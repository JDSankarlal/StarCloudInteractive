#pragma once

#include "SplashScreen.h"


cocos2d::CCScene* SplashScreen::StartScene()
{
	cocos2d::CCScene *StartScene = cocos2d::CCScene::create();
	SplashScreen *layer = SplashScreen::create();
	StartScene->addChild(layer);
	return StartScene;

}

bool SplashScreen::init()
{
	if (!cocos2d::CCLayer::init())
	{
		return false;
	}

	cocos2d::CCSize visibleSize = cocos2d::CCDirector::sharedDirector()->getVisibleSize();
	cocos2d::CCPoint origin = cocos2d::CCDirector::sharedDirector()->getVisibleOrigin();
	cocos2d::CCSprite* pSprite = cocos2d::CCSprite::create("Assets/SplashScreen.png");
	pSprite->setPosition(cocos2d::ccp(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	this->addChild(pSprite, 0);
	this->runAction(cocos2d::CCSequence::create(
		cocos2d::CCDelayTime::create(0.5),
		cocos2d::CCCallFunc::create(this,
			callfunc_selector(SplashScreen::loadSplash)),
		NULL));
	return true;
}

void SplashScreen::loadSplash()
{
	cocos2d::CCDirector::sharedDirector()->replaceScene(cocos2d::TransitionFade::create(2.5,MenuScene::create()));
}