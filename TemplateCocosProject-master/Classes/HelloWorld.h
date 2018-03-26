#pragma once
#include "cocos2d.h"

#include "AudioPlayer.h"
#include "Player.h"
#include "Platforms.h"
#include "SimpleAudioEngine.h"
#include <thread>
#include <string>
//#include <CCVector.h>
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

	bool onContactPreSolve(PhysicsContact& contact, PhysicsContactPreSolve& contact2)
	{
		auto shapeA = contact.getShapeA();
		auto bodyA = shapeA->getBody();

		auto shapeB = contact.getShapeB();
		auto bodyB = shapeB->getBody();

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

	cocos2d::Director *director;

private:
	AudioPlayer * audio = new AudioPlayer;
	Player* players[4] = {new Player(this,1,0),new Player(this,1,1),new Player(this,1,2),new Player(this,1,3)};

	void contact();

	//Put variables and sprites and stuff here
	cocos2d::Sprite* background = cocos2d::Sprite::create("Assets/Background.png");
	cocos2d::Sprite* menu;
	cocos2d::Sprite* resumeBtn;
	cocos2d::Sprite* restartBtn;
	cocos2d::Sprite* quitBtn;

	bool gamePaused = false;
	bool resumeBtnActive = false;
	bool restartBtnActive = false;
	bool quitBtnActive = false;


};


