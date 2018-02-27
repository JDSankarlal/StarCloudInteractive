#pragma once 
#include "HelloWorld.h"



USING_NS_CC;
using namespace std;

Scene* HelloWorld::createScene()
{
	auto scenepb = HelloWorld::createWithPhysics();
//	scenepb->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	auto world = HelloWorld::create();
	scenepb->addChild(world);
	//setScene(world);
	scenepb->getPhysicsWorld()->setGravity(Vec2(0, -1500));
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

	//Players
	
	p1->setPosition(director->getOpenGLView()->getFrameSize().width / 2, director->getOpenGLView()->getFrameSize().height / 2);
	p2->setPosition(director->getOpenGLView()->getFrameSize().width / 2+80, director->getOpenGLView()->getFrameSize().height / 2);

	pf1 = new Platforms(this, 1, 500);
	auto pf2 = new Platforms(this, 2, 500);
	//auto pf3 = new Platforms(this, 2, 500);
	//auto pf4 = new Platforms(this, 2, 500);
	//auto pf5 = new Platforms(this, 2, 500);
	//pf5->setPosition(visibleSize.width / 2, visibleSize.height / 2 - 350);
	//pf4->setPosition(visibleSize.width / 2, visibleSize.height / 2 - 300);
	//pf3->setPosition(visibleSize.width / 2, visibleSize.height / 2 - 250);
	pf2->setPosition(visibleSize.width / 2, visibleSize.height / 2 - 200);
	pf1->setPosition(visibleSize.width / 2, visibleSize.height / 2 - 150);

	background->setScaleX(visibleSize.width / background->getContentSize().width);
	background->setScaleY(visibleSize.height / background->getContentSize().height);
	background->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	addChild(background, -1);

	contact();

	this->scheduleUpdate();
	audio->setAudio("Audio/Battle_Time_V3.mp3");
	audio->play(true);

	return true;
}

//Updates movement per frame
void HelloWorld::update(float dt)
{			   	
	p1->movementUpdate(0);
	p2->movementUpdate(1);
	
		
}

void HelloWorld::contact()
{
	auto contactListener =
		EventListenerPhysicsContact::create();
	contactListener->onContactBegin = [](PhysicsContact& contact)
	{

		auto shapeA = contact.getShapeA();
		auto bodyA = shapeA->getBody();

		auto shapeB = contact.getShapeB();
		auto bodyB = shapeB->getBody();
		OutputDebugStringA("Collision\n");
		return true;
	};

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
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