#pragma once
#include "cocos2d.h"
#include "AudioPlayer.h"
#include "SimpleAudioEngine.h"
#include "controller.h"
#include <thread>
#include <string>

#pragma comment(lib,"Xinput9_1_0.lib")
class MenuScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);
	void DrawWorld(); 
	void update(float);
	// implement the "static create()" method manually
	CREATE_FUNC(MenuScene);


	AudioPlayer *audio = new AudioPlayer;

	cocos2d::Director *director;

	cocos2d::Sprite* background = cocos2d::Sprite::create("Assets/Main_Menu.png");
	cocos2d::Sprite* playBtn;
	cocos2d::Sprite* optionsBtn;
	cocos2d::Sprite* quitBtn;
	  	
private:
	//Put variables and sprites and stuff here
	bool playBtnActive = true;
	bool optionsBtnActive  = false;
	bool quitBtnActive = false;

};
