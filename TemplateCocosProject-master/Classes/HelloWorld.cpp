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
	auto pf2 = new Platforms(this, 1, true, 250, 70);
	auto pf3 = new Platforms(this, 1, true, 250, 70);
	auto pf4 = new Platforms(this, 1, true, 250, 70);
	auto pf1 = new Platforms(this, 1, true, 250, 70);
	auto pf5 = new Platforms(this, 1, true, 250, 70);
	auto pf6 = new Platforms(this, 1, true, 250, 70);
	auto pf7 = new Platforms(this, 1, true, 250, 70);
	auto pf8 = new Platforms(this, 1, true, 250, 70);
	auto pf9 = new Platforms(this, 1, true, 250, 70);

	pf2->setPosition(visibleSize.width / 2 - 300, visibleSize.height / 2 - 350);
	pf3->setPosition(visibleSize.width / 2 + 300, visibleSize.height / 2 - 350);

	pf7->setPosition(visibleSize.width / 2, visibleSize.height / 2 + -75);

	pf8->setPosition(visibleSize.width / 2 - 525, visibleSize.height / 2 + -150);
	pf9->setPosition(visibleSize.width / 2 + 525, visibleSize.height / 2 + -150);

	pf4->setPosition(visibleSize.width / 2 + 700, visibleSize.height / 2 + 50);
	pf1->setPosition(visibleSize.width / 2 - 700, visibleSize.height / 2 + 50);

	pf5->setPosition(visibleSize.width / 2 + 175, visibleSize.height / 2 + 250);
	pf6->setPosition(visibleSize.width / 2 - 175, visibleSize.height / 2 + 250);
	

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

	menu = Sprite::create("Assets/grey.png");
	menu->setPosition(visibleSize.width / 2, (visibleSize.height / 2));
	menu->setScale(4);
	menu->setAnchorPoint(Vec2(0.5f, 0.5f));

	this->addChild(menu, -2);

	pause = Sprite::create("Assets/Button_Pause.png");
	pause->setPosition(visibleSize.width / 2, (visibleSize.height / 2) + 300);
	pause->setScale(1);
	pause->setAnchorPoint(Vec2(0.5f, 0.5f));
	this->addChild(pause, -2);

	restartBtn = Sprite::create("Assets/Button_Dark_Restart.png");
	restartBtn->setPosition(visibleSize.width / 2, (visibleSize.height / 2) -50);
	restartBtn->setScale(0.6);
	restartBtn->setAnchorPoint(Vec2(0.5f, 0.5f));
	this->addChild(restartBtn, -2);

	resumeBtn = Sprite::create("Assets/Button_Dark_PauseMenuResume.png");
	resumeBtn->setPosition(visibleSize.width / 2, (visibleSize.height / 2) + 75);
	resumeBtn->setScale(0.6);
	resumeBtn->setAnchorPoint(Vec2(0.5f, 0.5f));
	this->addChild(resumeBtn, -2);

	quitBtn = Sprite::create("Assets/Button_Dark_PauseMenuQuit.png");
	quitBtn->setPosition(visibleSize.width / 2, (visibleSize.height / 2) - 175);
	quitBtn->setScale(0.6);
	quitBtn->setAnchorPoint(Vec2(0.5f, 0.5f));
	this->addChild(quitBtn, -2);

	//Collision stuff
	contact();

	//call update
	this->scheduleUpdate();

	//Background Audio
	audio->stopAll();
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
			a->addImpulse(0, 0);
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
					pause->setGlobalZOrder(4);
					Director::getInstance()->getRunningScene()->getPhysicsWorld()->setSpeed(0); //pause game
					menu->setGlobalZOrder(3); //move menu forwards
					for(auto &a : players)
					{
						a->pause();//pauses player update
						for(auto &b : a->getChildren())
							b->pause();	//stops the player animation
					}
					//pauses projectials
					paused = Director::getInstance()->getActionManager()->pauseAllRunningActions();

				} else  //if game paused
				{
					gamePaused = false; //set game to unpaused
					resumeBtnActive = false;
					restartBtnActive = false;
					quitBtnActive = false;
					pause->setGlobalZOrder(-2);
					resumeBtn->setGlobalZOrder(-2);
					restartBtn->setGlobalZOrder(-2);
					quitBtn->setGlobalZOrder(-2);
					menu->setGlobalZOrder(-2); //move menu back
					Director::getInstance()->getRunningScene()->getPhysicsWorld()->setSpeed(1); //Resume game
					//this->resume();
					for(auto &a : players)
					{
						a->resume();
						for(auto &b : a->getChildren())
							b->resume();
					}
					Director::getInstance()->getActionManager()->resumeTargets(paused);
				}
			}

			if(gamePaused)
			{
				if(resumeBtnActive)
				{

					resumeBtn->setScale(0.8f);

					if(controllers.ButtonStroke(a, A))
					{
						gamePaused = false; //set game to unpaused
						resumeBtnActive = false;
						restartBtnActive = false;
						quitBtnActive = false;
						pause->setGlobalZOrder(-2);
						resumeBtn->setGlobalZOrder(-2);
						restartBtn->setGlobalZOrder(-2);
						quitBtn->setGlobalZOrder(-2);
						menu->setGlobalZOrder(-2); //move menu back
						Director::getInstance()->getRunningScene()->getPhysicsWorld()->setSpeed(1); //Resume game
						for(auto &a : players)
						{
							a->resume();
							for(auto &b : a->getChildren())
								b->resume();
						}
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
							resumeBtn->setScale(0.6);
							resumeBtnActive = false;
						}
					}
				} else if(restartBtnActive)
				{
					restartBtn->setScale(0.8f);

					if(controllers.ButtonStroke(a, A))
					{
						audio->stopAll();
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
							restartBtn->setScale(0.6);
							restartBtnActive = false;
						}
						if(moveD.yAxis > 0)
						{
							resumeBtnActive = true;
							restartBtn->setScale(0.6);
							restartBtnActive = false;
						}
					}
				} else if(quitBtnActive)
				{

					quitBtn->setScale(0.8f);

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
							quitBtn->setScale(0.6);
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