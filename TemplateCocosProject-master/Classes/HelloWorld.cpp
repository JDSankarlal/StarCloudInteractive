#pragma once 
#include "HelloWorld.h"
#include "TutorialScene.h"

USING_NS_CC;
using namespace std;

Scene* HelloWorld::createScene()
{

	auto scenepb = HelloWorld::createWithPhysics();
	///Creates collision boxes around PhysicsBodies
	//scenepb->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

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
	short count = 0;
	for(auto &a : players)
	{
		a->setPosition(director->getOpenGLView()->getFrameSize().width / 2 + (80 * count++), director->getOpenGLView()->getFrameSize().height / 2);
	}

	//platforms
	auto pf2 = new Platforms(this, 1, true, 500);

	pf2->setPosition(visibleSize.width / 2, visibleSize.height / 2 - 200);
	//pf1->setPosition(visibleSize.width / 2 + 100, visibleSize.height / 2 + 150);

	//Place Background
	background->setScaleX(visibleSize.width / background->getContentSize().width);
	background->setScaleY(visibleSize.height / background->getContentSize().height);
	background->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	addChild(background, -1);

	//Director::getInstance()->getRunningScene()->getPhysicsWorld()->setSpeed(1); //resume game

	//Place Pause Menu

	//menu = Sprite::create("Assets/idfk.png");
	//menu->setPosition(visibleSize.width / 2, (visibleSize.height / 2));
	//menu->setScale(1);
	//menu->setAnchorPoint(Vec2(0.5f, 0.5f));

	menu = Sprite::create("Assets/newPaused.png");
	menu->setPosition(visibleSize.width / 2, (visibleSize.height / 2));
	menu->setScale(1.6);
	menu->setAnchorPoint(Vec2(0.5f, 0.5f));

	this->addChild(menu, -2);

	restartBtn = Sprite::create("Assets/restart.png");
	restartBtn->setPosition(visibleSize.width / 2, (visibleSize.height / 2));
	restartBtn->setScale(1);
	restartBtn->setAnchorPoint(Vec2(0.5f, 0.5f));
	this->addChild(restartBtn, -2);

	resumeBtn = Sprite::create("Assets/resumeButn.png");
	resumeBtn->setPosition(visibleSize.width / 2, (visibleSize.height / 2) + 125);
	resumeBtn->setScale(1);
	resumeBtn->setAnchorPoint(Vec2(0.5f, 0.5f));
	this->addChild(resumeBtn, -2);

	quitBtn = Sprite::create("Assets/quitbtn.png");
	quitBtn->setPosition(visibleSize.width / 2, (visibleSize.height / 2) - 125);
	quitBtn->setScale(1);
	quitBtn->setAnchorPoint(Vec2(0.5f, 0.5f));
	this->addChild(quitBtn, -2);

	player1 = Sprite::create("Assets/UI Elements/Player Names/Player1.png");
	player1->setPosition(100, visibleSize.height - 100);
	player1->setScale(.5);
	this->addChild(player1, 2);

	player2 = Sprite::create("Assets/UI Elements/Player Names/Player2.png");
	player2->setPosition(250, visibleSize.height - 100);
	player2->setScale(.5);
	this->addChild(player2, 2);

	player3 = Sprite::create("Assets/UI Elements/Player Names/Player3.png");
	player3->setPosition(400, visibleSize.height - 100);
	player3->setScale(.5);
	this->addChild(player3, 2);

	player4 = Sprite::create("Assets/UI Elements/Player Names/Player4.png");
	player4->setPosition(550, visibleSize.height - 100);
	player4->setScale(.5);
	this->addChild(player4, 2);

	healthBar1 = Sprite::create("Assets/UI Elements/Health Bars/White.png");
	healthBar1->setPosition(player1->getPositionX() + 35, player1->getPositionY()-10);
	healthBar1->setScale(.5);
	this->addChild(healthBar1, 2);

	healthBar2 = Sprite::create("Assets/UI Elements/Health Bars/White.png");
	healthBar2->setPosition(player2->getPositionX() + 35, player2->getPositionY()-10);
	healthBar2->setScale(.5);
	this->addChild(healthBar2, 2);

	healthBar3 = Sprite::create("Assets/UI Elements/Health Bars/White.png");
	healthBar3->setPosition(player3->getPositionX() + 35, player3->getPositionY()-10);
	healthBar3->setScale(.5);
	this->addChild(healthBar3, 2);

	healthBar4 = Sprite::create("Assets/UI Elements/Health Bars/White.png");
	healthBar4->setPosition(player4->getPositionX() + 35, player4->getPositionY()-10);
	healthBar4->setScale(.5);
	this->addChild(healthBar4, 2);

	lives1 = Sprite::create("Assets/UI Elements/Lives/3_Lives.png");
	lives1->setPosition(player1->getPositionX() - 35, player1->getPositionY() - 20);
	lives1->setScale(.5);
	this->addChild(lives1, 2);

	lives2 = Sprite::create("Assets/UI Elements/Lives/3_Lives.png");
	lives2->setPosition(player2->getPositionX() - 35, player2->getPositionY() - 20);
	lives2->setScale(.5);
	this->addChild(lives2, 2);

	lives3 = Sprite::create("Assets/UI Elements/Lives/3_Lives.png");
	lives3->setPosition(player3->getPositionX() - 35, player3->getPositionY() - 20);
	lives3->setScale(.5);
	this->addChild(lives3, 2);

	lives4 = Sprite::create("Assets/UI Elements/Lives/3_Lives.png");
	lives4->setPosition(player4->getPositionX() - 35, player4->getPositionY() - 20);
	lives4->setScale(.5);
	this->addChild(lives4, 2);
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
void HelloWorld::update(float dt)
{
	static XBoxInput controllers;
	controllers.DownloadPackets(4);

	short count = 0;
	for(auto &a : players)
	{
		if(a->getSprite()->getPositionY() < -200)
		{
			a->setVel(0, 0);
			a->setPosition(director->getOpenGLView()->getFrameSize().width / 2 + (80 * count++), director->getOpenGLView()->getFrameSize().height / 2);
		}
	}

	for(int a = 0; a < 4; a++)
		if(controllers.GetConnected(a))
		{

			Stick moveD, moveU;

			static int count[] {0,0,0,0}, til = 20;

			controllers.GetSticks(a, moveD, moveU);
			static Vector<Node*>paused;
			if(controllers.ButtonStroke(a, Start)) //If start pressed on controller
			{

				if(!gamePaused) //if game not paused
				{
					gamePaused = true; //set game to paused
					resumeBtnActive = true;
					resumeBtn->setGlobalZOrder(4);
					restartBtn->setGlobalZOrder(4);
					quitBtn->setGlobalZOrder(4);
					Director::getInstance()->getRunningScene()->getPhysicsWorld()->setSpeed(0); //pause game
					menu->setGlobalZOrder(3); //move menu forwards
					for(auto &a : players)
						a->pause();
					paused = Director::getInstance()->getActionManager()->pauseAllRunningActions();

				} else  //if game paused
				{
					gamePaused = false; //set game to unpaused
					resumeBtnActive = false;
					restartBtnActive = false;
					quitBtnActive = false;
					resumeBtn->setGlobalZOrder(-2);
					restartBtn->setGlobalZOrder(-2);
					quitBtn->setGlobalZOrder(-2);
					menu->setGlobalZOrder(-2); //move menu back
					Director::getInstance()->getRunningScene()->getPhysicsWorld()->setSpeed(1); //Resume game
					//this->resume();
					for(auto &a : players)
						a->resume();
					Director::getInstance()->getActionManager()->resumeTargets(paused);
				}
			}

			if(gamePaused)
			{
				if(resumeBtnActive)
				{

					resumeBtn->setScale(1.3f);

					if(controllers.ButtonStroke(a, A))
					{
						gamePaused = false; //set game to unpaused
						resumeBtnActive = false;
						restartBtnActive = false;
						quitBtnActive = false;
						resumeBtn->setGlobalZOrder(-2);
						restartBtn->setGlobalZOrder(-2);
						quitBtn->setGlobalZOrder(-2);
						menu->setGlobalZOrder(-2); //move menu back
						Director::getInstance()->getRunningScene()->getPhysicsWorld()->setSpeed(1); //Resume game
						for(auto &a : players)
							a->resume();
						Director::getInstance()->getActionManager()->resumeTargets(paused);
					}
					if(moveD.yAxis == 0)
					{
						count[a] = til;
					}

					if(count[a]++ > til)
					{
						count[a] = 0;

						if(moveD.yAxis < 0)
						{
							restartBtnActive = true;
							resumeBtn->setScale(1);
							resumeBtnActive = false;
						}
					}
				} else if(restartBtnActive)
				{
					restartBtn->setScale(1.3f);

					if(controllers.ButtonStroke(a, A))
					{
						audio->stop();
						Director::getInstance()->replaceScene(HelloWorld::createScene());
					}
					if(moveD.yAxis == 0)
					{

						count[a] = til;
					}

					if(count[a]++ > til)
					{
						count[a] = 0;

						if(moveD.yAxis < 0)
						{
							quitBtnActive = true;
							restartBtn->setScale(1);
							restartBtnActive = false;
						}
						if(moveD.yAxis > 0)
						{
							resumeBtnActive = true;
							restartBtn->setScale(1);
							restartBtnActive = false;
						}
					}
				} else if(quitBtnActive)
				{

					quitBtn->setScale(1.3f);

					if(controllers.ButtonStroke(a, A))
					{
						Director::getInstance()->end();
					}
					if(moveD.yAxis == 0)
					{
						count[a] = til;
					}

					if(count[a]++ > til)
					{
						count[0] = 0;
						if(moveD.yAxis > 0)
						{
							restartBtnActive = true;
							quitBtn->setScale(1);
							quitBtnActive = false;
						}
					}
				}
			}
		}
}

void HelloWorld::contact()
{
	auto contactListener =
		EventListenerPhysicsContact::create();
	auto world = this;


	contactListener->onContactBegin = CC_CALLBACK_1(HelloWorld::onContactBegin,this);
	//used for calculating
	contactListener->onContactPreSolve = CC_CALLBACK_2(HelloWorld::onContactPreSolve,this);


	getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

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

}