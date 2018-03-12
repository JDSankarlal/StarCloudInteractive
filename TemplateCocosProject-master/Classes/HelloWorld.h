#pragma once
#include "cocos2d.h"

#include "AudioPlayer.h"
#include "Player.h"
#include "Platforms.h"
#include "SimpleAudioEngine.h"
#include <thread>
#include <string>
#include "controller.h"

#pragma comment(lib,"Xinput9_1_0.lib")
using namespace Input;
class HelloWorld : public cocos2d::Scene
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
	CREATE_FUNC(HelloWorld);


	//Background sprite
	//cocos2d::Sprite * sprite,*BG = cocos2d::Sprite::create("Assets/test level.png");
	//cocos2d::Sprite3D *s3d = cocos2d::Sprite3D::create("Assets/test 3d model.c3b");
	float movex, movey, vely;


	
	cocos2d::Director *director;

private:
	AudioPlayer * audio = new AudioPlayer;
	Player* players[4] = {new Player(this,1),new Player(this,1),new Player(this,1),new Player(this,1)};

	void contact();
	
	//Put variables and sprites and stuff here
	cocos2d::Sprite* background = cocos2d::Sprite::create("Assets/Level_BG.png");
	cocos2d::Sprite* menu;
	cocos2d::Sprite* resumeBtn;
	cocos2d::Sprite* restartBtn;
	cocos2d::Sprite* quitBtn;
	
	bool gamePaused = false;
	bool resumeBtnActive = false;
	bool restartBtnActive = false;
	bool quitBtnActive = false;


};


