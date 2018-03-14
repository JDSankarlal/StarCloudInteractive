#pragma once 
#include "TutorialScene.h"
#include "PauseScene.h"
#include "HelloWorld.h"



USING_NS_CC;
using namespace std;

Scene* TutorialScene::createScene()
{
	auto scenepb = TutorialScene::createWithPhysics();
	//	scenepb->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	auto world = TutorialScene::create();
	scenepb->addChild(world);
	//setScene(world);
	scenepb->getPhysicsWorld()->setGravity(Vec2(0, -1500));
	return scenepb;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in TutorialSceneScene.cpp\n");
}

// on "init" you need to initialize your instance
bool TutorialScene::init()
{

	//////////////////////////////
	// 1. super init first
	if(!Scene::init())
		return false;

	director = Director::getInstance();
	auto visibleSize = director->getVisibleSize();
	Vec2 origin = director->getVisibleOrigin();

	//Players
	short count = 0;
	for(auto &a : players)
	{
		a->setPosition(director->getOpenGLView()->getFrameSize().width / 2 + (80 * count++), director->getOpenGLView()->getFrameSize().height / 2);
	}

	//platforms
	pf1 = new Platforms(this, 1,false ,200);
	auto pf2 = new Platforms(this, 2, true, 500);

	pf2->setPosition(visibleSize.width / 2, visibleSize.height / 2 - 200);
	pf1->setPosition(visibleSize.width / 2 + 100, visibleSize.height / 2 + 150);

	//Place Background
	background->setScaleX(visibleSize.width / background->getContentSize().width);
	background->setScaleY(visibleSize.height / background->getContentSize().height);
	background->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	addChild(background, -1);

	//menu screen
	menu = Sprite::create("pics/newPaused.png");
	menu->setPosition(visibleSize.width / 2, (visibleSize.height / 2));
	menu->setScale(1.6);
	menu->setAnchorPoint(Vec2(0.5f, 0.5f));

	this->addChild(menu, -2);

	skipBtn = Sprite::create("Skip.png");
	skipBtn->setPosition(visibleSize.width / 2, (visibleSize.height / 2));
	skipBtn->setScale(1);
	skipBtn->setAnchorPoint(Vec2(0.5f, 0.5f));
	this->addChild(skipBtn, -2);

	resumeBtn = Sprite::create("pics/resumeButn.png");
	resumeBtn->setPosition(visibleSize.width / 2, (visibleSize.height / 2) + 125);
	resumeBtn->setScale(1);
	resumeBtn->setAnchorPoint(Vec2(0.5f, 0.5f));
	this->addChild(resumeBtn, -2);

	quitBtn = Sprite::create("pics/quitbtn.png");
	quitBtn->setPosition(visibleSize.width / 2, (visibleSize.height / 2) - 125);
	quitBtn->setScale(1);
	quitBtn->setAnchorPoint(Vec2(0.5f, 0.5f));
	this->addChild(quitBtn, -2);

	//Collision stuff
	contact();
	
	//call update
	this->scheduleUpdate();
	
	//Background Audio
	audio->setAudio("Audio/Battle_Time_V3.mp3");
	audio->play(true);

	return true;
}

//Updates movement per frame
void TutorialScene::update(float dt)
{
	static XBoxInput controllers;
	controllers.DownloadPackets(4);

	short count = 0;
	for(auto &a : players)
	{
		a->movementUpdate(count++);


		if(a->getSprite()->getPositionY() < -200)
		{
			a->setPosition(director->getOpenGLView()->getFrameSize().width / 2, director->getOpenGLView()->getFrameSize().height / 2);
		}

	}

	if (controllers.GetConnected(0))
	{
		
		//OutputDebugStringA(string("Controller: "+std::to_string(index)+'\n').c_str());
		Stick moveD, moveU;

		static int count, til = 20;
		controllers.GetSticks(0, moveD, moveU);

		if (controllers.ButtonStroke(0, Start)) //If start pressed on controller
		{
			if (gamePaused == false) //if game not paused
			{
				gamePaused = true; //set game to paused
				resumeBtnActive = true;
				resumeBtn->setGlobalZOrder(4);
				skipBtn->setGlobalZOrder(4);
				quitBtn->setGlobalZOrder(4);
				Director::getInstance()->getRunningScene()->getPhysicsWorld()->setSpeed(0); //pause game
				menu->setGlobalZOrder(3); //move menu forwards
				//Director::getInstance()->pushScene(PauseScene::createScene());
			}

			else if (gamePaused == true) //if game paused
			{
				gamePaused = false; //set game to unpaused
				resumeBtnActive = false;
				skipBtnActive = false;
				quitBtnActive = false;
				resumeBtn->setGlobalZOrder(-2);
				skipBtn->setGlobalZOrder(-2);
				quitBtn->setGlobalZOrder(-2);
				menu->setGlobalZOrder(-2); //move menu back
				Director::getInstance()->getRunningScene()->getPhysicsWorld()->setSpeed(1); //Resume game
				
			}
		}
		
		if (gamePaused == true)
		{
			if (resumeBtnActive)
			{
				
				resumeBtn->setScale(1.3f);

				if (controllers.ButtonStroke(0, A))
				{
					gamePaused = false; //set game to unpaused
					resumeBtnActive = false;
					skipBtnActive = false;
					quitBtnActive = false;
					resumeBtn->setGlobalZOrder(-2);
					skipBtn->setGlobalZOrder(-2);
					quitBtn->setGlobalZOrder(-2);
					menu->setGlobalZOrder(-2); //move menu back
					Director::getInstance()->getRunningScene()->getPhysicsWorld()->setSpeed(1); //Resume game
				}
				if (moveD.yAxis == 0)
				{
					count = til;
				}
				if (count++ > til) {
					count = 0;
					if (moveD.yAxis < 0)
					{
						skipBtnActive = true;
						resumeBtn->setScale(1);
						resumeBtnActive = false;
					}
				}
			}
			else if (skipBtnActive)
			{
				skipBtn->setScale(1.3f);

				if (controllers.ButtonStroke(0, A))
				{
					Director::getInstance()->replaceScene(HelloWorld::createScene());
				}
				if (moveD.yAxis == 0)
				{
					count = til;
				}
				if (count++ > til) {
					count = 0;
					if (moveD.yAxis < 0)
					{
						quitBtnActive = true;
						skipBtn->setScale(1);
						skipBtnActive = false;
					}
					if (moveD.yAxis > 0)
					{
						resumeBtnActive = true;
						skipBtn->setScale(1);
						skipBtnActive = false;
					}
				}
			}
			else if (quitBtnActive)
			{

				quitBtn->setScale(1.3f);

				if (controllers.ButtonStroke(0, A))
				{
					Director::getInstance()->end();
				}
				if (moveD.yAxis == 0)
				{
					count = til;
				}
				if (count++ > til) {
					count = 0;
					if (moveD.yAxis > 0)
					{
						skipBtnActive = true;
						quitBtn->setScale(1);
						quitBtnActive = false;
					}
				}
			}
		}
	}
}

void TutorialScene::contact()
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

		//if (shapeA->getCategoryBitmask() == 1 && shapeB->getCategoryBitmask() == 2) {
		//	for (auto &a : *players)
		//		shapeA->getCenter();
		//}
		//else
		//	if (shapeA->getCategoryBitmask() == 2 && shapeB->getCategoryBitmask() == 1) {
		//
		//	}
		return true;
	};

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
}


void TutorialScene::menuCloseCallback(Ref* pSender)
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

void TutorialScene::DrawWorld()
{

}