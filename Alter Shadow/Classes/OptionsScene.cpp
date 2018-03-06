#pragma once 
#include "MenuScene.h"
#include "HelloWorld.h"
#include "OptionsScene.h"
USING_NS_CC;
using namespace std;
using namespace Input;
Scene* OptionsScene::createScene()
{
	return  OptionsScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in MenuSceneScene.cpp\n");
}

// on "init" you need to initialize your instance
bool OptionsScene::init()
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
	background->setScaleY(visibleSize.height / background->getContentSize().height);
	background->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	addChild(background, -1);

	optionsHeader = Sprite::create("pics/OptionsBtn.png");
	optionsHeader->setPosition(visibleSize.width / 2, (visibleSize.height / 2) + 200);
	optionsHeader->setScale(2);
	optionsHeader->setAnchorPoint(Vec2(0.5f, 0.5f));
	this->addChild(optionsHeader, 2);

	fullScrBtn = Sprite::create("pics/fullscreen.png");
	fullScrBtn->setPosition(visibleSize.width / 2, (visibleSize.height / 2));
	fullScrBtn->setScale(1);
	fullScrBtn->setAnchorPoint(Vec2(0.5f, 0.5f));
	this->addChild(fullScrBtn, 2);

	musicBtn = Sprite::create("pics/soundBtn.png");
	musicBtn->setPosition(visibleSize.width / 2, (visibleSize.height / 2) - 125);
	musicBtn->setScale(1);
	musicBtn->setAnchorPoint(Vec2(0.5f, 0.5f));
	this->addChild(musicBtn, 2);

	backBtn = Sprite::create("pics/backBtn.png");
	backBtn->setPosition(visibleSize.width / 2, (visibleSize.height / 2) - 250);
	backBtn->setScale(1);
	backBtn->setAnchorPoint(Vec2(0.5f, 0.5f));
	this->addChild(backBtn, 2);


	//call update
	this->scheduleUpdate();



	//Background Audio
	audio->setAudio("Audio/Battle_Time_V3.mp3");
	audio->play(true);

	return true;
}

//Updates movement per frame
void OptionsScene::update(float index)
{
	static XBoxInput controllers;
	controllers.DownloadPackets(4);


	if (controllers.GetConnected(index))
	{
		Stick moveD, moveU;
		static int count, til = 20;
		controllers.GetSticks(index, moveD, moveU);

		if (fullScrBtnActive)
		{
			fullScrBtn->setScale(1.3f);

			if (controllers.ButtonPress(index, A))
			{
				//make fullscreen
			}
			if (moveD.yAxis == 0)
			{
				count = til;
			}
			if (count++>til) {
				count = 0;
				if (moveD.yAxis < 0)
				{
					musicBtnActive = true;
					fullScrBtn->setScale(1);
					fullScrBtnActive = false;
				}
			}
		}

		else if (musicBtnActive)
		{
			musicBtn->setScale(1.3f);

			if (controllers.ButtonPress(index, A))
			{
				
			}
			if (moveD.yAxis == 0)
			{
				count = til;
			}
			if (count++ > til) {
				count = 0;
				if (moveD.yAxis < 0)
				{
					backBtnActive = true;
					musicBtn->setScale(1);
					musicBtnActive = false;
				}
				if (moveD.yAxis > 0)
				{
					fullScrBtnActive = true;
					musicBtn->setScale(1);
					musicBtnActive = false;
				}
			}
		}
			
		else if (backBtnActive)
		{
			backBtn->setScale(1.3f);

			if (controllers.ButtonPress(index, A))
			{
				//Director::getInstance()->replaceScene(OptionsScene::createScene());
			}
			if (controllers.ButtonPress(index, B))
			{
				Director::getInstance()->replaceScene(MenuScene::createScene());
			}
			if (moveD.yAxis == 0)
			{
				count = til;
			}
			if (count++ > til) {
				count = 0;
				if (moveD.yAxis > 0)
				{
					musicBtnActive = true;
					backBtn->setScale(1);
					backBtnActive = false;
				}
			}

		}
		

		

	}
}

void OptionsScene::menuCloseCallback(Ref* pSender)
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

void OptionsScene::DrawWorld()
{

}