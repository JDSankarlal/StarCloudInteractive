#pragma once 
#include "HelloWorld.h"
#include "SimpleAudioEngine.h"
#include <thread>


USING_NS_CC;
using namespace Input;
using namespace std;

Scene* HelloWorld::createScene()
{
	auto scenepb = HelloWorld::createWithPhysics();
	scenepb->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	auto world = HelloWorld::create();
	scenepb->addChild(world);
	//setScene(world);
	scenepb->getPhysicsWorld()->setGravity(Vec2(0, -1000));
	return scenepb;
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

	p1 = new Player(this);
	p1->setPosition(director->getOpenGLView()->getFrameSize().width / 2, director->getOpenGLView()->getFrameSize().height / 2);
	pf1 = new Platforms(this, 1500);
	pf1->setPosition(visibleSize.width / 2, visibleSize.height / 2 - 200);

	background->setScaleX(visibleSize.width / background->getContentSize().width);
	background->setScaleY(visibleSize.height / background->getContentSize().height);
	background->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	addChild(background, -1);
										
	
	this->scheduleUpdate();
	audio->setAudio("Audio/Battle_Time(All together).mp3");
	audio->play(true);


	auto contactListener =
		EventListenerPhysicsContact::create();
	contactListener->onContactBegin = [](PhysicsContact& contact)
	{
		CCLOG("contact begin");
		auto shapeA = contact.getShapeA();
		auto bodyA = shapeA->getBody();

		auto shapeB = contact.getShapeB();
		auto bodyB = shapeB->getBody();
		return true;
	};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

	return true;
}

//Updates movement per frame
void HelloWorld::update(float dt)
{

	controllers->DownloadPackets();

#pragma region Controller Stuff
	if(controllers->GetConnected(0))
	{
		Stick moveL, moveR;
		controllers->GetSticks(0, moveL, moveR);
		int move = 110;
		p1->setVelX(moveL.xAxis * move);
		if(moveL.xAxis * move == 0)
			NULL;
		else if(moveL.xAxis * move < 0)
			p1->getSprite()->setFlippedX(true);
		else
			p1->getSprite()->setFlippedX(false);

#pragma region Jumping
		//Jumping
		if(controllers->ButtonPress(0, A) && !hasJumped)
		{
			//p1->setPosition(p1->getSprite()->getPosition().x, p1->getSprite()->getContentSize().height * p1->getSprite()->getScaleY() / 2);
			p1->setVelY(400);
			hasJumped = true;
		}
		if(controllers->ButtonRelease(0, A))
			hasJumped = false;

		//jump();
		//int floor = 110;
		//if(movey >= floor)
		//	movey--;
		//else
		//	movey = floor;

#pragma endregion

#pragma region Switching Platforms
		//Dimentional colour change
		static bool colPress;
		Color3B colours[] {Color3B(1 * 255,1 * 255,1 * 255),Color3B(1 * 255,0 * 255,0 * 255),Color3B(0 * 255,1 * 255,1 * 255)};
		if(controllers->ButtonPress(0, LB) && !colPress)
		{
			colPress = true;

			if(colChange - 1 >= 0 && colChange - 1 < 3)
				p1->getSprite()->setColor(Color3B(colours[--colChange]));


		}


		if(controllers->ButtonPress(0, RB) && !colPress)
		{
			colPress = true;
			if(colChange + 1 >= 0 && colChange + 1 < 3)
				p1->getSprite()->setColor(Color3B(colours[++colChange]));
		}
		if(controllers->ButtonRelease(0, RB) && controllers->ButtonRelease(0, LB))
			colPress = false;
		p1->platformSwitch(colChange);
#pragma endregion

	}
#pragma endregion
	//float pfHeight = pf1->getSprite()->getCenterRect().size.height * pf1->getSprite()->getScaleY(),
	//	   pHeight = p1->getSprite()->getCenterRect().size.height * p1->getSprite()->getScaleY();
	//if((p1->getSprite()->getPosition().y - (pHeight / 2)) <= (pf1->getSprite()->getPosition().y + (pfHeight / 2)))
	//{
	//	p1->getBody()->setGravityEnable(false);
	//	p1->setPosition(p1->getSprite()->getPosition().x, pf1->getSprite()->getPosition().y + (pHeight / 2) + (pf1->getSprite()->getContentSize().height*pf1->getSprite()->getScaleY()) / 2,p1->getSprite()->getPositionZ() );
	////	p1->setVelY(0);
	//} else
	//	p1->getBody()->setGravityEnable(true);
													
//	p1->setPosition(, , 0);
}

bool HelloWorld::onContactBegin(PhysicsContact &contact)
{
	auto a = contact.getShapeA()->getBody(), b = contact.getShapeA()->getBody();
	OutputDebugStringA("Colision!!!!!!!!!!\n\n");
	return true;
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

void HelloWorld::DrawWorld()
{
	//background = Sprite::create("pics/Level_BG.png");
	//background->setAnchorPoint(Vec2(0.5f, 0.5f));
	//background->setPosition(director->getWinSizeInPixels().width / 2, director->getWinSizeInPixels().height / 2);
	//this->addChild(background, -100);
	//
	//Platform = Sprite::create("pics/empty.png");
	//Platform->setPosition(200, 100);
	//Platform->setScale(0.30f);
	//Platform->setAnchorPoint(Vec2(0.5f, 0.5f));
	//this->addChild(Platform);
}