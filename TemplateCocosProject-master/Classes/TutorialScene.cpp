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
		a->setPosition(director->getOpenGLView()->getFrameSize().width / 2 + (80 * count++), director->getOpenGLView()->getFrameSize().height / 2);
	}

	//for (auto &a : sheep)
	//{
	//	a->setPosition(director->getOpenGLView()->getFrameSize().width / 2 + (80 * count++), director->getOpenGLView()->getFrameSize().height / 2, 0);
	//}


	//platforms
	auto pf2 = new Platforms(this, 1, true, 250, 70);
	auto pf3 = new Platforms(this, 1, true, 250, 70);
	auto pf4 = new Platforms(this, 1, true, 250, 70);
	auto pf5 = new Platforms(this, 1, true, 250, 70);

	pf3->setPosition(visibleSize.width / 2 + 175, visibleSize.height / 2 +0);
	pf4->setPosition(visibleSize.width / 2 - 175, visibleSize.height / 2 +0);

	pf5->setPosition(visibleSize.width / 2 - 300, visibleSize.height / 2 - 210);
	pf2->setPosition(visibleSize.width / 2 + 300, visibleSize.height / 2 - 210);

	//this->addChild(sheep, 1);
	//Place Background
	background->setScaleX(visibleSize.width / background->getContentSize().width);
	background->setScaleY(visibleSize.height / background->getContentSize().height);
	background->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	addChild(background, -1);

	//Pause Menu
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
	scroll1->setPosition(visibleSize.width / 2, (visibleSize.height / 2)+300);
	scroll1->setScale(1.2);
	scroll1->setAnchorPoint(Vec2(0.5f, 0.5f));

	this->addChild(scroll1, 2);

	scroll2 = Sprite::create("Assets/tutorial2.png");
	scroll2->setPosition(visibleSize.width / 2, (visibleSize.height / 2)+300);
	scroll2->setScale(1.2);
	scroll2->setAnchorPoint(Vec2(0.5f, 0.5f));

	this->addChild(scroll2, -2);

	scroll3 = Sprite::create("Assets/tutorial3.png");
	scroll3->setPosition(visibleSize.width / 2, (visibleSize.height / 2)+300);
	scroll3->setScale(1.2);
	scroll3->setAnchorPoint(Vec2(0.5f, 0.5f));

	this->addChild(scroll3, -2);

	scroll4 = Sprite::create("Assets/tutorial4.png");
	scroll4->setPosition(visibleSize.width / 2, (visibleSize.height / 2)+300);
	scroll4->setScale(1.2);
	scroll4->setAnchorPoint(Vec2(0.5f, 0.5f));

	this->addChild(scroll4, -2);

	scroll5 = Sprite::create("Assets/tutorial5.png");
	scroll5->setPosition(visibleSize.width / 2, (visibleSize.height / 2)+300);
	scroll5->setScale(1.2);
	scroll5->setAnchorPoint(Vec2(0.5f, 0.5f));

	this->addChild(scroll5, -2);

	scroll6 = Sprite::create("Assets/tutorial6.png");
	scroll6->setPosition(visibleSize.width / 2, (visibleSize.height / 2)+300);
	scroll6->setScale(1.2);
	scroll6->setAnchorPoint(Vec2(0.5f, 0.5f));

	this->addChild(scroll6, -2);

	scroll7 = Sprite::create("Assets/tutorial7.png");
	scroll7->setPosition(visibleSize.width / 2, (visibleSize.height / 2)+300);
	scroll7->setScale(1.2);
	scroll7->setAnchorPoint(Vec2(0.5f, 0.5f));

	this->addChild(scroll7, -2);

	scroll8 = Sprite::create("Assets/tutorial8.png");
	scroll8->setPosition(visibleSize.width / 2, (visibleSize.height / 2)+300);
	scroll8->setScale(1.2);
	scroll8->setAnchorPoint(Vec2(0.5f, 0.5f));

	this->addChild(scroll8, -2);

	scroll9 = Sprite::create("Assets/tutorial9.png");
	scroll9->setPosition(visibleSize.width / 2, (visibleSize.height / 2)+300);
	scroll9->setScale(1.2);
	scroll9->setAnchorPoint(Vec2(0.5f, 0.5f));

	this->addChild(scroll9, -2);

	scroll10 = Sprite::create("Assets/tutorial10.png");
	scroll10->setPosition(visibleSize.width / 2, (visibleSize.height / 2) + 300);
	scroll10->setScale(1.2);
	scroll10->setAnchorPoint(Vec2(0.5f, 0.5f));

	this->addChild(scroll10, -2);

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
	  for(int a=0;a<4;a++)
	if(controllers.GetConnected(a))
	{

		//OutputDebugStringA(string("Controller: "+std::to_string(index)+'\n').c_str());
		Stick moveD, moveU;

		static int count, til = 20;
		controllers.GetSticks(a, moveD, moveU);

		if(controllers.ButtonStroke(a, Start)) //If start pressed on controller
		{
			if(!gamePaused) //if game not paused
			{
				gamePaused = true; //set game to paused
				resumeBtnActive = true;
				resumeBtn->setGlobalZOrder(4);
				restartBtn->setGlobalZOrder(4);
				quitBtn->setGlobalZOrder(4);
				Director::getInstance()->getRunningScene()->getPhysicsWorld()->setSpeed(a); //pause game
				menu->setGlobalZOrder(3); //move menu forwards
				//Director::getInstance()->pushScene(PauseScene::createScene());
			}

			else if(gamePaused) //if game paused
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
				}
				if(moveD.yAxis == 0)
				{
					count = til;
				}
				if(count++ > til)
				{
					count = 0;
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
					Director::getInstance()->replaceScene(TutorialScene::createScene());
				}
				if(moveD.yAxis == 0)
				{
					count = til;
				}
				if(count++ > til)
				{
					count = 0;
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
					count = til;
				}
				if(count++ > til)
				{
					count = 0;
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

void TutorialScene::contact()
{
	auto contactListener =
		EventListenerPhysicsContact::create();
	contactListener->onContactPreSolve = [](PhysicsContact& contact, PhysicsContactPreSolve& contact2)
	{
		auto shapeA = contact.getShapeA();
		auto bodyA = shapeA->getBody();

		auto shapeB = contact.getShapeB();
		auto bodyB = shapeB->getBody();
		//printf("Tag1 = %d\nTag2 = %d\n\n", bodyA->getTag(), bodyB->getTag());
		//OutputDebugStringA("Colision dicision\n");

		return false;
	};
	contactListener->onContactBegin = [](PhysicsContact& contact)
	{

		auto shapeA = contact.getShapeA();
		auto bodyA = shapeA->getBody();

		auto shapeB = contact.getShapeB();
		auto bodyB = shapeB->getBody();
		OutputDebugStringA("Collision\n");

		if(bodyA->getTag() == bodyB->getTag())
			return false;
		return true;
	};

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

void TutorialScene::DrawWorld()
{

}