#pragma once
#include <cocos2d.h>
#include "HelloWorldScene.h"

class SplashScreen :public cocos2d::CCLayer
{
public:
	virtual bool init();
	static cocos2d::CCScene* splashScene();
	void loadSplash();
	CREATE_FUNC(SplashScreen);
};