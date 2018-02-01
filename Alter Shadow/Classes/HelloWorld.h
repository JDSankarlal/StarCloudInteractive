#pragma once
#include "cocos2d.h"
#include "controller.h"
#include "AudioPlayer.h"
#include <string>

class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
	//Jump
	void jump();
    //update function
	void update(float) ;
	// implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	
	cocos2d::Sprite * sprite,*BG = cocos2d::Sprite::create("pics/test level.png");
	cocos2d::Sprite3D *s3d = cocos2d::Sprite3D::create("pics/test 3d model.c3b");
	float movex,movey,vely;
	bool hasJumped;
	short colChange;
	AudioPlayer *audio=new AudioPlayer;
	Input::XBoxInput* controllers=new Input::XBoxInput;
	cocos2d::Director *director;
};


