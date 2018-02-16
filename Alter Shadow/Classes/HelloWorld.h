#pragma once
#include "cocos2d.h"
#include "controller.h"
#include "AudioPlayer.h"
#include "Player.h"
#include "Platforms.h"
#include <string>

#pragma comment(lib,"Xinput9_1_0.lib")
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
	void update(float) ;
	// implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	
	//Background sprite
	//cocos2d::Sprite * sprite,*BG = cocos2d::Sprite::create("pics/test level.png");
	//cocos2d::Sprite3D *s3d = cocos2d::Sprite3D::create("pics/test 3d model.c3b");
	float movex,movey,vely;
	bool hasJumped;
	short colChange;
	AudioPlayer *audio=new AudioPlayer;
	Player *p1;


	Input::XBoxInput* controllers=new Input::XBoxInput;
	cocos2d::Director *director;

private:
	//HelloWorld* world;
	//void setScene(static HelloWorld* scene)
	//{
	//	world = scene;
	//}
	//Put variables and sprites and stuff here
	Sprite* background = Sprite::create("pics/Level_BG.png"); 
	Platforms* pf1;
	bool onContactBegin(cocos2d::PhysicsContact &contact);
	int jumpCount;
};


