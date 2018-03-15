#pragma once 
#include "MenuScene.h"
#include "HelloWorld.h"
#include "OptionsScene.h"
#include "TutorialScene.h"

USING_NS_CC;
using namespace std;
using namespace Input;
Scene* MenuScene::createScene()
{
	return  MenuScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in MenuSceneScene.cpp\n");
}

// on "init" you need to initialize your instance
bool MenuScene::init()
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

	playBtn = Sprite::create("Assets/Button_Play.png");
	playBtn->setPosition((visibleSize.width / 2) + 10, visibleSize.height / 2);
	playBtn->setScale(2);
	playBtn->setAnchorPoint(Vec2(0.5f, 0.5f));
	this->addChild(playBtn, 2);

	optionsBtn = Sprite::create("Assets/Button_Options.png");
	optionsBtn->setPosition((visibleSize.width / 2) + 10, (visibleSize.height / 2) - 125);
	optionsBtn->setScale(2);
	optionsBtn->setAnchorPoint(Vec2(0.5f, 0.5f));
	this->addChild(optionsBtn, 2);

	quitBtn = Sprite::create("Assets/Button_Quit.png");
	quitBtn->setPosition((visibleSize.width / 2) - 5, (visibleSize.height / 2) - 250);
	quitBtn->setScale(2);
	quitBtn->setAnchorPoint(Vec2(0.5f, 0.5f));
	this->addChild(quitBtn, 2);

	//call update
	this->scheduleUpdate();

	//Background Audio
	audio->stop();
	audio->setAudio("Audio/Menu_Music(full).mp3");
	audio->play(true);

	return true;
}

//Updates movement per frame
void MenuScene::update(float index)
{
	static XBoxInput controllers;
	controllers.DownloadPackets(4);


	if (controllers.GetConnected(index))
	{
	
		Stick moveD, moveU;
		static int count,til=20;
		controllers.GetSticks(index, moveD, moveU);
		if (playBtnActive)
		{
			playBtn->setScale(2.5f);
	
			if (controllers.ButtonStroke(index, A))
			{
				audio->stop();
				Director::getInstance()->replaceScene(HelloWorld::createScene());
			}
			if (moveD.yAxis == 0)
			{
				count = til;
			}
			if (count++>til) {
				count = 0;
				if (moveD.yAxis < 0)
				{
					optionsBtnActive = true;
					playBtn->setScale(2);
					playBtnActive = false;
				}
			}
		}
		else if (optionsBtnActive)
		{
			optionsBtn->setScale(2.5f);
	
			if (controllers.ButtonStroke(index, A))
			{
				audio->stop();
				Director::getInstance()->replaceScene(OptionsScene::createScene());
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
					optionsBtn->setScale(2);
					optionsBtnActive = false;
				}
				if (moveD.yAxis > 0)
				{
					playBtnActive = true;
					optionsBtn->setScale(2);
					optionsBtnActive = false;
				}
			}
		}
		else if (quitBtnActive)
		{
			quitBtn->setScale(2.5f);
	
			if (controllers.ButtonStroke(index, A))
			{
				audio->stop();
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
					optionsBtnActive = true;
					quitBtn->setScale(2);
					quitBtnActive = false;
				}
			}
			
		}
	
	}
}

void MenuScene::menuCloseCallback(Ref* pSender)
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

void MenuScene::DrawWorld()
{

}
