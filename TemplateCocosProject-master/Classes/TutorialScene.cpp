#pragma once 
#include "TutorialScene.h"

USING_NS_CC;
using namespace std;

Scene* TutorialScene::createScene()
{
	auto scenepb = TutorialScene::createWithPhysics();
	////Creates collision boxes around PhysicsBodies
	scenepb->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	auto world = TutorialScene::create();
	scenepb->addChild(world);
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
		a->setPosition(director->getOpenGLView()->getFrameSize().width / 2 - 600 - (40 * count++), director->getOpenGLView()->getFrameSize().height / 2 -150);
	}

	sheep->setPosition(director->getOpenGLView()->getFrameSize().width / 2 + (170 * count++), director->getOpenGLView()->getFrameSize().height / 2 -150);
	//sheep->setPosition(visibleSize.width / 2, (visibleSize.height / 2));

	//platforms
	auto pf2 = new Platforms(this, 1, true, 400, 115);
	auto pf3 = new Platforms(this, 1, true, 400, 115);
	auto pf4 = new Platforms(this, 1, true, 400, 115);
	auto pf5 = new Platforms(this, 1, true, 400, 115);

	pf3->setPosition(visibleSize.width / 2 + 225, visibleSize.height / 2 +0);
	pf4->setPosition(visibleSize.width / 2 - 225, visibleSize.height / 2 +0);

	pf5->setPosition(visibleSize.width / 2 - 550, visibleSize.height / 2 - 250);
	pf2->setPosition(visibleSize.width / 2 + 550, visibleSize.height / 2 - 250);

	//Place Background
	background->setScaleX(visibleSize.width / background->getContentSize().width);
	background->setScaleY(visibleSize.height / background->getContentSize().height);
	background->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	addChild(background, -1);

	//Pause Menu
	menu = Sprite::create("Assets/grey.png");
	menu->setPosition(visibleSize.width / 2, (visibleSize.height / 2));
	menu->setScale(4);
	menu->setAnchorPoint(Vec2(0.5f, 0.5f));

	this->addChild(menu, -2);

	paused = Sprite::create("Assets/Button_Pause.png");
	paused->setPosition(visibleSize.width / 2, (visibleSize.height / 2) +300);
	paused->setScale(1);
	paused->setAnchorPoint(Vec2(0.5f, 0.5f));
	this->addChild(paused, -2);

	restartBtn = Sprite::create("Assets/Button_Dark_Restart.png");
	restartBtn->setPosition(visibleSize.width / 2, (visibleSize.height / 2)-125);
	restartBtn->setScale(0.6);
	restartBtn->setAnchorPoint(Vec2(0.5f, 0.5f));
	this->addChild(restartBtn, -2);

	skipBtn = Sprite::create("Assets/Button_Dark_Skip.png");
	skipBtn->setPosition(visibleSize.width / 2, (visibleSize.height / 2) );
	skipBtn->setScale(0.6);
	skipBtn->setAnchorPoint(Vec2(0.5f, 0.5f));
	this->addChild(skipBtn, -2);

	resumeBtn = Sprite::create("Assets/Button_Dark_PauseMenuResume.png");
	resumeBtn->setPosition(visibleSize.width / 2, (visibleSize.height / 2) + 125);
	resumeBtn->setScale(0.6);
	resumeBtn->setAnchorPoint(Vec2(0.5f, 0.5f));
	this->addChild(resumeBtn, -2);

	quitBtn = Sprite::create("Assets/Button_Dark_PauseMenuQuit.png");
	quitBtn->setPosition(visibleSize.width / 2, (visibleSize.height / 2) - 250);
	quitBtn->setScale(0.6);
	quitBtn->setAnchorPoint(Vec2(0.5f, 0.5f));
	this->addChild(quitBtn, -2);
	
	//
	//
	//
	//
	//
	//
	//Tutorial Scrolls
	scroll1 = Sprite::create("Assets/tutorial1.png");
	scroll1->setPosition(visibleSize.width / 2, (visibleSize.height / 2) + 300);
	scroll1->setScale(3);
	scroll1->setAnchorPoint(Vec2(0.5f, 0.5f));

	this->addChild(scroll1, 2);
	scrolls.push_back(scroll1);
	
	scroll2 = Sprite::create("Assets/tutorial2.png");
	scroll2->setPosition(visibleSize.width / 2, (visibleSize.height / 2) + 300);
	scroll2->setScale(3);
	scroll2->setAnchorPoint(Vec2(0.5f, 0.5f));

	this->addChild(scroll2, -2);
	scrolls.push_back(scroll2);

	scroll3 = Sprite::create("Assets/tutorial3.png");
	scroll3->setPosition(visibleSize.width / 2, (visibleSize.height / 2)+300);
	scroll3->setScale(3);
	scroll3->setAnchorPoint(Vec2(0.5f, 0.5f));

	this->addChild(scroll3, -2);
	scrolls.push_back(scroll3);
	
	//Try Moving
	tryMove = Sprite::create("Assets/ALS.png");
	tryMove->setPosition(visibleSize.width / 2, (visibleSize.height / 2) + 300);
	tryMove->setScale(3);
	tryMove->setAnchorPoint(Vec2(0.5f, 0.5f));

	this->addChild(tryMove, -2);
	scrolls.push_back(tryMove);

	//Try dashing
	tryDash = Sprite::create("Assets/TryRTLT.png");
	tryDash->setPosition(visibleSize.width / 2, (visibleSize.height / 2) + 300);
	tryDash->setScale(3);
	tryDash->setAnchorPoint(Vec2(0.5f, 0.5f));

	this->addChild(tryDash, -2);
	scrolls.push_back(tryDash);

	//try attacking
	TryAttack = Sprite::create("Assets/TryX.png");
	TryAttack->setPosition(visibleSize.width / 2, (visibleSize.height / 2) + 300);
	TryAttack->setScale(3);
	TryAttack->setAnchorPoint(Vec2(0.5f, 0.5f));

	this->addChild(TryAttack, -2);
	scrolls.push_back(TryAttack);

	//after sheep 1 dead
	scroll4 = Sprite::create("Assets/tutorial4.png");
	scroll4->setPosition(visibleSize.width / 2, (visibleSize.height / 2)+300);
	scroll4->setScale(3);
	scroll4->setAnchorPoint(Vec2(0.5f, 0.5f));

	this->addChild(scroll4, -2);
	scrolls.push_back(scroll4);

	//use heavy attack
	scroll5 = Sprite::create("Assets/YorBbeam.png");
	scroll5->setPosition(visibleSize.width / 2, (visibleSize.height / 2)+300);
	scroll5->setScale(3);
	scroll5->setAnchorPoint(Vec2(0.5f, 0.5f));

	this->addChild(scroll5, -2);
	scrolls.push_back(scroll5);

	//after that sheep dead
	scroll8 = Sprite::create("Assets/tutorial8.png");
	scroll8->setPosition(visibleSize.width / 2, (visibleSize.height / 2)+300);
	scroll8->setScale(3);
	scroll8->setAnchorPoint(Vec2(0.5f, 0.5f));

	this->addChild(scroll8, -2);
	scrolls.push_back(scroll8);

	scroll9 = Sprite::create("Assets/tutorial9.png");
	scroll9->setPosition(visibleSize.width / 2, (visibleSize.height / 2)+300);
	scroll9->setScale(3);
	scroll9->setAnchorPoint(Vec2(0.5f, 0.5f));

	this->addChild(scroll9, -2);
	scrolls.push_back(scroll9);

	scroll10 = Sprite::create("Assets/tutorial10.png");
	scroll10->setPosition(visibleSize.width / 2, (visibleSize.height / 2) + 300);
	scroll10->setScale(3);
	scroll10->setAnchorPoint(Vec2(0.5f, 0.5f));

	this->addChild(scroll10, -2);
	scrolls.push_back(scroll10);

	//press start scroll
	startScroll = Sprite::create("Assets/Start.png");
	startScroll->setPosition(visibleSize.width / 2, (visibleSize.height / 2) + 300);
	startScroll->setScale(3);
	startScroll->setAnchorPoint(Vec2(0.5f, 0.5f));

	this->addChild(startScroll, -2);
	scrolls.push_back(startScroll);

	//Collision stuff
	contact();

	//call update
	this->scheduleUpdate();

	//Background Audio
	
	audio->setAudio("Audio/Battle_Time_V3.mp3");
	audio->play(true);
	
	OutputDebugStringA("Finish Init\n\n");
	return true;
}

//Updates movement per frame
void TutorialScene::update(float dt)
{
	theRealDT += dt;

	static XBoxInput controllers;

	controllers.DownloadPackets(4);

	short count = 0;
	for(auto &a : players)
	{
		
		if(a->getSprite()->getPositionY() < -200)
		{
			a->setPosition(director->getOpenGLView()->getFrameSize().width / 2, director->getOpenGLView()->getFrameSize().height / 2);
		}

	}
	static Vector<Node*>pausedActions;
	  for(int a=0;a<4;a++)
	if(controllers.GetConnected(a))
	{

		//OutputDebugStringA(string("Controller: "+std::to_string(index)+'\n').c_str());
		Stick moveD, moveU;

		static int count[]{0,0,0,0}, til = 20;
		controllers.GetSticks(a, moveD, moveU);

		if(controllers.ButtonStroke(a, Start)) //If start pressed on controller
		{
			if(!gamePaused) //if game not paused
			{
				gamePaused = true; //set game to paused
				resumeBtnActive = true;
				resumeBtn->setGlobalZOrder(4);
				skipBtn->setGlobalZOrder(4);
				restartBtn->setGlobalZOrder(4);
				quitBtn->setGlobalZOrder(4);
				paused->setGlobalZOrder(4);
				Director::getInstance()->getRunningScene()->getPhysicsWorld()->setSpeed(a); //pause game
				menu->setGlobalZOrder(3); //move menu forwards
				for(auto &a : players)
				{
					a->pause();//pauses player update
					for(auto &b : a->getChildren())
						b->pause();	//stops the player animation
				}
				pausedActions = Director::getInstance()->getActionManager()->pauseAllRunningActions();
			}

			else if(gamePaused) //if game paused
			{
				gamePaused = false; //set game to unpaused
				resumeBtnActive = false;
				skipBtnActive = false;
				restartBtnActive = false;
				quitBtnActive = false;
				paused->setGlobalZOrder(-2);
				skipBtn->setGlobalZOrder(-2);
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
				Director::getInstance()->getActionManager()->resumeTargets(pausedActions);
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
					paused->setGlobalZOrder(-2);
					resumeBtn->setGlobalZOrder(-2);
					restartBtn->setGlobalZOrder(-2);
					skipBtn->setGlobalZOrder(-2);
					quitBtn->setGlobalZOrder(-2);
					menu->setGlobalZOrder(-2); //move menu back
					Director::getInstance()->getRunningScene()->getPhysicsWorld()->setSpeed(1); //Resume game
					for(auto &a : players)
					{
						a->resume();
						for(auto &b : a->getChildren())
							b->resume();
					}
					Director::getInstance()->getActionManager()->resumeTargets(pausedActions);
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
						skipBtnActive = true;
						resumeBtn->setScale(0.6);
						resumeBtnActive = false;
					}
				}
			} 
			else if(skipBtnActive)
			{
				skipBtn->setScale(0.8f);

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
						restartBtnActive = true;
						skipBtn->setScale(0.6);
						skipBtnActive = false;
					}
					if(moveD.yAxis > 0)
					{
						resumeBtnActive = true;
						skipBtn->setScale(0.6);
						skipBtnActive = false;
					}
				}
			} 
			else if (restartBtnActive)
			{
				restartBtn->setScale(0.8f);

				if (controllers.ButtonStroke(a, A))
				{
					audio->stop();
					Director::getInstance()->replaceScene(TutorialScene::createScene());
				}
				if (moveD.yAxis == 0)
				{
					count[a] = til;
				}
				if (count[a]++ > til)
				{
					count[a] = 0;
					if (moveD.yAxis < 0)
					{
						quitBtnActive = true;
						restartBtn->setScale(0.6);
						restartBtnActive = false;
					}
					if (moveD.yAxis > 0)
					{
						skipBtnActive = true;
						restartBtn->setScale(0.6);
						restartBtnActive = false;
					}
				}
			}
			else if(quitBtnActive)
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
					count[a] = 0;
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

	if (sheep->getHP() <= 0)
	{
		sheep->onDeath();
	}

	if (onStart == true)
	{
		Director::getInstance()->getRunningScene()->getPhysicsWorld()->setSpeed(0);
		for(auto &a : players)
		{
			a->pause();//pauses player update
			for(auto &b : a->getChildren())
				b->pause();	//stops the player animation
		}
	}
	  if (theRealDT >= 3)
	  {
		  
		  if (scrolls[0]->getZOrder() == 2)
		  {
			  scrolls[0]->setZOrder(-2);
			  scrolls[1]->setZOrder(2);
		  }
		  else if (scrolls[1]->getZOrder() == 2 && theRealDT >= 6)
		  {
			  scrolls[1]->setZOrder(-2);
			  scrolls[2]->setZOrder(2);
		  }
		  else if (scrolls[2]->getZOrder() == 2 && theRealDT >= 9)
		  {
			  scrolls[2]->setZOrder(-2);
			  scrolls[3]->setZOrder(2);
			  onStart = false;
			  Director::getInstance()->getRunningScene()->getPhysicsWorld()->setSpeed(1);
			  for(auto &a : players)
			  {
				  a->resume();
				  for(auto &b : a->getChildren())
					  b->resume();
			  }
		  }
		  else if (scrolls[3]->getZOrder() == 2 && theRealDT >= 12)
		  {
			  scrolls[3]->setZOrder(-2);
			  scrolls[4]->setZOrder(2);
		  }
		  else if (scrolls[4]->getZOrder() == 2 && theRealDT >= 15 && players[0]->getPosition().x >= 1150)
		  {
			  scrolls[4]->setZOrder(-2);
			  scrolls[5]->setZOrder(2);
		  }
		  else if (scrolls[5]->getZOrder() == 2 && theRealDT >= 20 && sheep->sheep1 == false)
		  {
			  scrolls[5]->setZOrder(-2);
			  scrolls[6]->setZOrder(2);
			  theRealDT = 0;
			  sheep->sheep2 = true;
		  }
		  else if (scrolls[6]->getZOrder() == 2 && theRealDT >= 3)
		  {
			  scrolls[6]->setZOrder(-2);
			  scrolls[7]->setZOrder(2);
		  }
		  else if (scrolls[7]->getZOrder() == 2 && theRealDT >= 6 && sheep->sheep2 == false)
		  {
			  scrolls[7]->setZOrder(-2);
			  scrolls[8]->setZOrder(2);
			  theRealDT = 0;
		  }
		  else if (scrolls[8]->getZOrder() == 2 && theRealDT >= 3)
		  {
			  scrolls[8]->setZOrder(-2);
			  scrolls[9]->setZOrder(2);
			  this->removeChild(sheep);
		  }
		  else if (scrolls[9]->getZOrder() == 2 && theRealDT >= 6)
		  {
			  scrolls[9]->setZOrder(-2);
			  scrolls[10]->setZOrder(2);
		  }
		  else if (scrolls[10]->getZOrder() == 2 && theRealDT >= 9)
		  {
			  scrolls[10]->setZOrder(-2);
			  scrolls[11]->setZOrder(2);
		  }
		  else if (scrolls[11]->getZOrder() == 2 && theRealDT >= 12)
		  {
			  
		  }

	  }
	OutputDebugStringA(string(to_string(theRealDT)+"\n").c_str());
}


void TutorialScene::contact()
{
	auto contactListener =
		EventListenerPhysicsContact::create();
	contactListener->onContactPreSolve = CC_CALLBACK_2(TutorialScene::onContactPreSolve,this);
	contactListener->onContactBegin = CC_CALLBACK_1(TutorialScene::onContactBegin, this);

	getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

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