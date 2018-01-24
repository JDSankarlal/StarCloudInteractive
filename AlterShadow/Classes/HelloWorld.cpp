#include "HelloWorld.h"
#include "SimpleAudioEngine.h"
#include <thread>


USING_NS_CC;
using namespace Input;
using namespace std;

Scene* HelloWorld::createScene()
{
	return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}




// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	//////////////////////////////
	// 1. super init first
	if(!Scene::init())
		return false;

	director = Director::getInstance();
	auto visibleSize = director->getVisibleSize();
	Vec2 origin = director->getVisibleOrigin();

	
	sprite = Sprite::create("pics/test player 2.png");
	sprite->setAnchorPoint(Vec2(0.5f, 0.5f));
	//sprite->setScale();
	sprite->setPosition3D(Vec3());
	
	addChild(sprite);
	
	BG->setScaleX(director->getOpenGLView()->getFrameSize().width / BG->getContentSize().width);
	BG->setScaleY(director->getOpenGLView()->getFrameSize().height / BG->getContentSize().height);
	BG->setPosition(director->getOpenGLView()->getFrameSize().width / 2, director->getOpenGLView()->getFrameSize().height / 2);
	addChild(BG, -1);

	this->scheduleUpdate();


	return true;
}

void HelloWorld::jump()
{

	movey += vely--;

}

//Updates movement per frame
void HelloWorld::update(float dt)
{
	auto spb = sprite->getPhysicsBody();
	//rezResize();
	OutputDebugStringA((std::to_string(dt) + '\n').c_str());
	controllers->DownloadPackets();
#pragma region Controller Stuff
	if(controllers->GetConnected(0))
	{
		Stick moveL, moveR;
		controllers->GetSticks(0, moveL, moveR);
		movex += moveL.xAxis * 7;

		if(moveL.xAxis * 7 == 0)
			NULL;
		else if(moveL.xAxis * 7 < 0)
			sprite->setFlippedX(true);
		else
			sprite->setFlippedX(false);

#pragma region Jumping
		//Jumping
		if(controllers->ButtonPress(0, A) && !hasJumped)
		{
			vely = 18;
			hasJumped = true;
		}
		if(controllers->ButtonRelease(0, A))
			hasJumped = false;

		jump();
		int floor = 110;
		if(movey >= floor)
			movey--;
		else
			movey = floor;

#pragma endregion

#pragma region Switching Platforms
		//Dimentional colour change
		static bool colPress;
		Color3B colours[] {Color3B(1 * 255,1 * 255,1 * 255),Color3B(1 * 255,0 * 255,0 * 255),Color3B(0 * 255,1 * 255,1 * 255)};
		if(controllers->ButtonPress(0, LB) && !colPress)
		{
			colPress = true;

			if(colChange - 1 >= 0 && colChange - 1 < 3)
				sprite->setColor(Color3B(colours[--colChange]));

		}


		if(controllers->ButtonPress(0, RB) && !colPress)
		{
			colPress = true;
			if(colChange + 1 >= 0 && colChange + 1 < 3)
				sprite->setColor(Color3B(colours[++colChange]));
		}
		if(controllers->ButtonRelease(0, RB) && controllers->ButtonRelease(0, LB))
			colPress = false;
#pragma endregion
	
	}
#pragma endregion

	sprite->setPosition3D(Vec3(director->getWinSize().width / 2 + movex, 100 + movey, 0));
}

void HelloWorld::menuCloseCallback(Ref* pSender)
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
