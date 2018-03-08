#include "EmptyScene.h"
#include "MenuScene.h"
#include <thread>
#include <chrono>

#define pause(x) std::this_thread::sleep_for(std::chrono::milliseconds(x))
USING_NS_CC;
Scene* EmptyScene::createScene()
{
	return  EmptyScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in MenuSceneScene.cpp\n");
}

// on "init" you need to initialize your instance
bool EmptyScene::init()
{

	//////////////////////////////
	// 1. super init first
	

	if(!Scene::init())
		return false;
	
	
	
	Director::getInstance()->replaceScene(MenuScene::createScene());
	//pause(3000);
	return true;
}


void EmptyScene::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif

	/*To navigate back to native iOS screen(if present) without quitting the application,
	do not use Director::getInstance()->end() and exit(0) as given above, instead trigger
	a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);

}


