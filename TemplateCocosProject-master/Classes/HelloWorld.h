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
		ParticleSystemQuad* explosionSystem = ParticleExplosion::create();
		explosionSystem->setSpeed(200);
		explosionSystem->setLife(0.05);
		explosionSystem->setTotalParticles(150);
		explosionSystem->setStartColor(ccc4f(0.0f,0.0f,0.0f,1));
		explosionSystem->setEndColor(ccc4f(138.f / 255, 43.f / 255, 226.f / 255, 1));
		explosionSystem->setStartColorVar(ccc4f(0.0f, 0.0f, 0.0f, 1));
		explosionSystem->setEndColorVar(ccc4f(138.f / 255, 43.f / 255, 226.f / 255, 1));
		//THE COLORS MAN, DO NOT REMOVE THE VARIANCE THING OTHERWISE IT WILL BE 100% RAINBOW AGAIN
		//BUT FEEL FREE TO PLAY AROUND WITH COLOUR COMBOS

		auto shapeA = contact.getShapeA();
		auto bodyA = shapeA->getBody();

		auto shapeB = contact.getShapeB();
		auto bodyB = shapeB->getBody();

		//printf("Tag1 = %d\nTag2 = %d\n\n", bodyA->getTag(), bodyB->getTag());
		//OutputDebugStringA("Colision dicision\n");
		if(bodyA->getName() == "Player")
		{
			if(bodyB->getName() == "Platform")
				for(auto &a : players)
					if(bodyA == a->getBody())
						a->resetDashes();

		}

		if((bodyA->getName() == "Projectile"))
		{
			if(bodyB->getOwner() != nullptr)
				if(bodyB->getName() == "Projectile")
				{
					bodyB->getOwner()->removeFromParent();
				}
			if(bodyA->getOwner() != nullptr)
			{
				if(bodyB->getName() != "Platform")
				{
					bodyB->setVelocity(bodyB->getVelocity() + ((bodyB->getPosition() - bodyA->getPosition()).getNormalized() * 200));

					for(auto &a : players)
						if(bodyB == a->getBody())
						{
							OutputDebugStringA("Hitting a player\n");
							addChild(explosionSystem);
							explosionSystem->setPosition(bodyA->getPosition());
							runAction(Sequence::create(

								CallFunc::create(a, callfunc_selector(Player::pause)),
								DelayTime::create(1.3),
								CallFunc::create(a, callfunc_selector(Player::resume)), 0));
						}
				}
				//for(int a = 0; a < 4; a++)
				//	if(bodyB->getOwner()->getParent() == players[a])
				//		players[a]->setInterupt(2);
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

		if(bodyA->getName() == "Player" && bodyB->getName() == "Platform")
		{
			for(auto &a : players)
				if(bodyA == a->getBody())
					a->resetJumps();
		} else if(bodyB->getName() == "Player" && bodyA->getName() == "Platform")
		{
			for(auto &a : players)
				if(bodyB == a->getBody())
					a->resetJumps();
		}

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
	cocos2d::Sprite* pause;
	cocos2d::Sprite* menu;
	cocos2d::Sprite* resumeBtn;
	cocos2d::Sprite* restartBtn;
	cocos2d::Sprite* quitBtn;

	bool gamePaused = false;
	bool resumeBtnActive = false;
	bool restartBtnActive = false;
	bool quitBtnActive = false;



};


