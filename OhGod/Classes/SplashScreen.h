#pragma once

#include "cocos2d.h"
#include "MenuScene.h"

class SplashScreen :public cocos2d::CCLayer
{
public:
	virtual bool init();
	static cocos2d::CCScene *StartScene();
	void loadSplash();
	CREATE_FUNC(SplashScreen);
};