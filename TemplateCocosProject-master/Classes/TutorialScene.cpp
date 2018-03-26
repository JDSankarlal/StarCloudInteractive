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

	sheep->setPosition(director->getOpenGLView()->getFrameSize().width / 2 + (90 * count++), director->getOpenGLView()->getFrameSize().height / 2 -100);
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
	//Tutorial Buttons
	ABtn = Sprite::create("Assets/AButton.png");
	ABtn->setPosition(visibleSize.width / 2 - 350, (visibleSize.height / 2) +300);
	ABtn->setScale(1);
	ABtn->setAnchorPoint(Vec2(0.5f, 0.5f));

	this->addChild(ABtn, -2);

	BBtn = Sprite::create("Assets/BButton.png");
	BBtn->setPosition(visibleSize.width / 2 +350, (visibleSize.height / 2)+300);
	BBtn->setScale(1);
	BBtn->setAnchorPoint(Vec2(0.5f, 0.5f));

	this->addChild(BBtn, -2);

	YBtn = Sprite::create("Assets/YButton.png");
	YBtn->setPosition(visibleSize.width / 2 +350, (visibleSize.height / 2)+300);
	YBtn->setScale(1);
	YBtn->setAnchorPoint(Vec2(0.5f, 0.5f));

	this->addChild(YBtn, -2);

	XBtn = Sprite::create("Assets/XButton.png");
	XBtn->setPosition(visibleSize.width / 2 -350, (visibleSize.height / 2)+300);
	XBtn->setScale(1);
	XBtn->setAnchorPoint(Vec2(0.5f, 0.5f));

	this->addChild(XBtn, -2);

	LBpr = Sprite::create("Assets/LB.png");
	LBpr->setPosition(visibleSize.width / 2 -350, (visibleSize.height / 2)+300);
	LBpr->setScale(1);
	LBpr->setAnchorPoint(Vec2(0.5f, 0.5f));

	this->addChild(LBpr, -2);

	RBpr = Sprite::create("Assets/RB.png");
	RBpr->setPosition(visibleSize.width / 2 +350, (visibleSize.height / 2)+300);
	RBpr->setScale(1);
	RBpr->setAnchorPoint(Vec2(0.5f, 0.5f));

	this->addChild(RBpr, -2);

	RTrgr = Sprite::create("Assets/RT.png");
	RTrgr->setPosition(visibleSize.width / 2 +350, (visibleSize.height / 2)+300);
	RTrgr->setScale(1);
	RTrgr->setAnchorPoint(Vec2(0.5f, 0.5f));

	this->addChild(RTrgr, -2);

	LTrgr = Sprite::create("Assets/LT.png");
	LTrgr->setPosition(visibleSize.width / 2 -350, (visibleSize.height / 2)+300);
	LTrgr->setScale(1);
	LTrgr->setAnchorPoint(Vec2(0.5f, 0.5f));

	this->addChild(LTrgr, -2);

	LStick = Sprite::create("Assets/LStick.png");
	LStick->setPosition(visibleSize.width / 2 -350, (visibleSize.height / 2)+300);
	LStick->setScale(1);
	LStick->setAnchorPoint(Vec2(0.5f, 0.5f));

	this->addChild(LStick, -2);
			
	startBtn = Sprite::create("Assets/TStartBtn.png");
	startBtn->setPosition(visibleSize.width / 2 +350, (visibleSize.height / 2)+300);
	startBtn->setScale(1);
	startBtn->setAnchorPoint(Vec2(0.5f, 0.5f));

	this->addChild(startBtn, -2);

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

	tryDash = Sprite::create("Assets/TryRTLT.png");
	tryDash->setPosition(visibleSize.width / 2, (visibleSize.height / 2) + 300);
	tryDash->setScale(3);
	tryDash->setAnchorPoint(Vec2(0.5f, 0.5f));

	this->addChild(tryDash, -2);
	scrolls.push_back(tryDash);

	TryAttack = Sprite::create("Assets/TryX.png");
	TryAttack->setPosition(visibleSize.width / 2, (visibleSize.height / 2) + 300);
	TryAttack->setScale(3);
	TryAttack->setAnchorPoint(Vec2(0.5f, 0.5f));

	this->addChild(TryAttack, -2);
	scrolls.push_back(TryAttack);

	scroll4 = Sprite::create("Assets/tutorial4.png");
	scroll4->setPosition(visibleSize.width / 2, (visibleSize.height / 2)+300);
	scroll4->setScale(3);
	scroll4->setAnchorPoint(Vec2(0.5f, 0.5f));

	this->addChild(scroll4, -2);
	scrolls.push_back(scroll4);

	scroll5 = Sprite::create("Assets/YorBbeam.png");
	scroll5->setPosition(visibleSize.width / 2, (visibleSize.height / 2)+300);
	scroll5->setScale(3);
	scroll5->setAnchorPoint(Vec2(0.5f, 0.5f));

	this->addChild(scroll5, -2);
	scrolls.push_back(scroll5);

	scroll6 = Sprite::create("Assets/tutorial6.png");
	scroll6->setPosition(visibleSize.width / 2, (visibleSize.height / 2)+300);
	scroll6->setScale(3);
	scroll6->setAnchorPoint(Vec2(0.5f, 0.5f));

	this->addChild(scroll6, -2);
	scrolls.push_back(scroll6);

	scroll7 = Sprite::create("Assets/tutorial7.png");
	scroll7->setPosition(visibleSize.width / 2, (visibleSize.height / 2)+300);
	scroll7->setScale(3);
	scroll7->setAnchorPoint(Vec2(0.5f, 0.5f));

	this->addChild(scroll7, -2);
	scrolls.push_back(scroll7);

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

	//Try button scrolls
	

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
					a->pause();
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
					a->resume();
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
					quitBtn->setGlobalZOrder(-2);
					menu->setGlobalZOrder(-2); //move menu back
					Director::getInstance()->getRunningScene()->getPhysicsWorld()->setSpeed(1); //Resume game
					for(auto &a : players)
						a->resume();
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

	if (onStart == true)
	{
		Director::getInstance()->getRunningScene()->getPhysicsWorld()->setSpeed(0);
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
		  else if (scrolls[5]->getZOrder() == 2 && theRealDT >= 20 && sheep1 == false)
		  {
			  scrolls[5]->setZOrder(-2);
			  scrolls[6]->setZOrder(2);
		  }
		  else if (scrolls[5]->getZOrder() == 2 && theRealDT >= 22)
		  {
			  scrolls[6]->setZOrder(-2);
			  scrolls[7]->setZOrder(2);
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