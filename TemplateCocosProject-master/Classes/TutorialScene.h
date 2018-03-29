#pragma once
#include "cocos2d.h"

#include "AudioPlayer.h"
#include "Player.h"
#include "Platforms.h"
#include "SimpleAudioEngine.h"
#include <thread>
#include <string>
#include "controller.h"
#include "HelloWorld.h"
#include "Sheep.h"
#include "time.h"

#pragma comment(lib,"Xinput9_1_0.lib")
using namespace Input;
class TutorialScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	//a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);
	//update function
	void update(float);
	// implement the "static create()" method manually
	CREATE_FUNC(TutorialScene);

	//Background sprite
	//cocos2d::Sprite * sprite,*BG = cocos2d::Sprite::create("Assets/test level.png");
	//cocos2d::Sprite3D *s3d = cocos2d::Sprite3D::create("Assets/test 3d model.c3b");
	float movex, movey, vely;
	
	cocos2d::Director *director;

private:

	bool onContactPreSolve(PhysicsContact& contact, PhysicsContactPreSolve& contact2)
	{
		auto shapeA = contact.getShapeA();
		auto bodyA = shapeA->getBody();

		auto shapeB = contact.getShapeB();
		auto bodyB = shapeB->getBody();

		players[0];
		//printf("Tag1 = %d\nTag2 = %d\n\n", bodyA->getTag(), bodyB->getTag());
		//OutputDebugStringA("Colision dicision\n");
		if((bodyA->getName() == "Projectile"))
		{
			bodyB->getOwner()->setPosition(bodyB->getPosition().x, bodyB->getPosition().y);
			if(bodyA->getOwner() != nullptr)
			{
				if(bodyB->getName() != "Platform")
					bodyB->setVelocity(bodyB->getVelocity() + ((bodyB->getPosition() - bodyA->getPosition()).getNormalized() * 200));
				for(int a = 0; a < 4; a++)
					if(bodyB->getOwner()->getParent() == players[a])
						players[a]->setInterupt(2);
				bodyA->getOwner()->removeFromParent();
			}

		} 
		return true;
	}

	bool onContactBegin(PhysicsContact& contact)
	{

		auto shapeA = contact.getShapeA();
		auto bodyA = shapeA->getBody();

		auto shapeB = contact.getShapeB();
		auto bodyB = shapeB->getBody();
		OutputDebugStringA("Collision\n");
		OutputDebugStringA((bodyA->getName() + " == " + bodyB->getName() + "\n").c_str());
		OutputDebugStringA((to_string(bodyA->getTag()) + " == " + to_string(bodyB->getTag()) + "\n").c_str());

		if((bodyA->getName() == "Projectile" || bodyB->getName() == "Projectile") && (bodyA->getTag() != bodyB->getTag()))
		{
			return true;
		} else if((bodyA->getName() == "Projectile" || bodyB->getName() == "Projectile") && (bodyA->getTag() == bodyB->getTag()))
		{
			return false;
		}


		OutputDebugStringA((to_string(bodyA->getTag()) + " == " + to_string(bodyB->getTag()) + "\n").c_str());

		if(bodyA->getName() == bodyB->getName())
			return false;
		return true;
	};


	void contact();

	AudioPlayer * audio = new AudioPlayer;
	Player* players[4] = {new Player(this,1,0),new Player(this,1,1),new Player(this,1,2),new Player(this,1,3)};
	Sheep* sheep = new Sheep(this, 1);
	
	//Put variables and sprites and stuff here
	//Sprites for background and Pause Menu0
	cocos2d::Sprite* background = cocos2d::Sprite::create("Assets/Background.png");
	cocos2d::Sprite* menu;
	cocos2d::Sprite* resumeBtn;
	cocos2d::Sprite* restartBtn;
	cocos2d::Sprite* quitBtn;
	cocos2d::Sprite* skipBtn;
	cocos2d::Sprite* paused;

	//Sprites for buttons
	cocos2d::Sprite* ABtn;
	cocos2d::Sprite* BBtn;
	cocos2d::Sprite* YBtn;
	cocos2d::Sprite* XBtn;
	cocos2d::Sprite* LBpr;
	cocos2d::Sprite* RBpr;
	cocos2d::Sprite* LTrgr;
	cocos2d::Sprite* RTrgr;
	cocos2d::Sprite* LStick;
	cocos2d::Sprite* startBtn;

	//Sprites for Scrolls
	cocos2d::Sprite* scroll1;
	cocos2d::Sprite* scroll2;
	cocos2d::Sprite* scroll3;
	cocos2d::Sprite* scroll4;
	cocos2d::Sprite* scroll5; 
	cocos2d::Sprite* scroll6;
	cocos2d::Sprite* scroll7;
	cocos2d::Sprite* scroll8;
	cocos2d::Sprite* scroll9;
	cocos2d::Sprite* scroll10;

	cocos2d::Sprite* tryMove;
	cocos2d::Sprite* tryDash;
	cocos2d::Sprite* TryAttack;

	std::vector<Sprite*>scrolls;

	bool onStart = true; // For some reason I can't put this stuff in the init function otherwise it crashes my computer so thats a good time
	double theRealDT = 0;
	//Bools
	bool gamePaused = false;
	bool resumeBtnActive = false;
	bool restartBtnActive = false;
	bool quitBtnActive = false;
	bool skipBtnActive = false;
};


