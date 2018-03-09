#pragma once
#include "cocos2d.h"

#include "AudioPlayer.h"
#include "SimpleAudioEngine.h"
#include "controller.h"
#include <thread>
#include <string>

#pragma comment(lib,"Xinput9_1_0.lib")
class PauseScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);
	void DrawWorld();
	//Jump
	//void jump();
	//update function
	void update(float);
	// implement the "static create()" method manually
	CREATE_FUNC(PauseScene);


	//Background sprite
	//cocos2d::Sprite *BG = cocos2d::Sprite::create("pics/idfk.png"), sprite;
	//cocos2d::Sprite3D *s3d = cocos2d::Sprite3D::create("pics/test 3d model.c3b");

	AudioPlayer *audio = new AudioPlayer;

	cocos2d::Director *director;

	cocos2d::Sprite* background = cocos2d::Sprite::create("pics/idfk.png");
	//cocos2d::Sprite* background = cocos2d::Sprite::create("pics/download.jpg");
	//cocos2d::Sprite* backBtn;
	//cocos2d::Sprite* musicBtn;
	//cocos2d::Sprite* fullScrBtn;
	//
	//cocos2d::Sprite* optionsHeader;
	//cocos2d::Sprite* quitBtn;

private:


	//bool fullScrBtnActive = true;
	//bool musicBtnActive = false;
	//bool backBtnActive = false;
	//bool playBtnActive = true;
	//bool optionsBtnActive = false;
	//bool quitBtnActive = false;
	//Put variables and sprites and stuff here

};
