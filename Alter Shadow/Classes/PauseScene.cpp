#pragma once 
#include "MenuScene.h"
#include "HelloWorld.h"
#include "PauseScene.h"
USING_NS_CC;
using namespace std;
using namespace Input;
Scene* PauseScene::createScene()
{
	return  PauseScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in MenuSceneScene.cpp\n");
}

// on "init" you need to initialize your instance
bool PauseScene::init()
{

	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
		return false;

	director = Director::getInstance();
	auto visibleSize = director->getVisibleSize();
	Vec2 origin = director->getVisibleOrigin();

	//Background
	background->setScaleX(visibleSize.width / background->getContentSize().width);
	background->setScaleY(visibleSize.height / background->getContentSize().height);// / background->getContentSize().height);
	background->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	addChild(background, -1);

	//call update
	this->scheduleUpdate();



	//Background Audio
	audio->setAudio("Audio/Battle_Time_V3.mp3");
	audio->play(true);

	return true;
}

//Updates movement per frame
void PauseScene::update(float index)
{
	static XBoxInput controllers;
	controllers.DownloadPackets(4);


	if (controllers.GetConnected(index))
	{
		Stick moveD, moveU;
		static int count, til = 20;
		controllers.GetSticks(index, moveD, moveU);
		if (controllers.ButtonStroke(0, Start)) //If start pressed on controller
		{
			//Director::getInstance()->popScene(float 1.1f);
		}



	}
}

void PauseScene::menuCloseCallback(Ref* pSender)
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

void PauseScene::DrawWorld()
{

}