#pragma once
#include "cocos2d.h"

#include "AudioPlayer.h"
#include "Player.h"
#include "Platforms.h"
#include "SimpleAudioEngine.h"
#include <thread>
#include <string>
#include <vector>
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
	void Win();
	void playerPause();
	void playerResume();
	void Countdown();
	//void jump();
	float rangeRandom(float min, float max);
	void shakeScreen(float dt);
	//update function
	void update(float);
	void explosion();
	// implement the "static create()" method manually
	CREATE_FUNC(HelloWorld);




	//Background sprite
	//cocos2d::Sprite * sprite,*BG = cocos2d::Sprite::create("Assets/test level.png");
	//cocos2d::Sprite3D *s3d = cocos2d::Sprite3D::create("Assets/test 3d model.c3b");
	float movex, movey, vely;

	bool onContactPreSolve(PhysicsContact& contact, PhysicsContactPreSolve& contact2)
	{
		auto explosionSystem = ParticleExplosion::create();
		explosionSystem->setSpeed(100);
		explosionSystem->setLife(0.1);
		explosionSystem->setLifeVar(0.2);
		explosionSystem->setTotalParticles(150);
		explosionSystem->setStartColor(Color4F(1, 1, 1, 1));
		explosionSystem->setEndColor(Color4F(75.f / 255, 0, 130.f / 255, 1));
		explosionSystem->setStartColorVar(ccc4f(0, 0, 0, 1));
		explosionSystem->setEndColorVar(ccc4f(12.f / 255, 12.f / 255, 12.f / 255, 1));

		//DO NOT REMOVE THE VARIANCE THING OTHERWISE IT WILL BE 100% RAINBOW AGAIN
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

		} else if((bodyA->getName() == "Projectile"))
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
					for(auto &a : players)
						if(bodyB == a->getBody())
						{
							//if(a->getDamage() / 50)
							//{
							a->setAttacking(false);
							if(bodyA->getOwner()->getParent()->getTag())
								bodyB->setVelocity(bodyB->getVelocity() + ((bodyB->getPosition() - bodyA->getPosition()).getNormalized() * 200 * (a->getDamage() / 50 + 1)*.75));
							else
								bodyB->setVelocity(bodyB->getVelocity() + ((bodyB->getPosition() - bodyA->getPosition()).getNormalized() * 200 * (a->getDamage() / 50 + 1)*.75)*1.5);


							OutputDebugStringA("Hitting a player\n");
							addChild(explosionSystem);
							explosionSystem->setPosition(bodyA->getPosition());
							if(bodyA->getOwner()->getParent()->getTag())
							{
								OutputDebugStringA("Now Thats a lot of Damage\n");
								a->setDamage(a->getDamage() + 25);
							} else
							{
								a->setDamage(a->getDamage() + 10);
							}
							runAction(Sequence::create(
								CallFunc::create(a, callfunc_selector(Player::pause)),
								DelayTime::create(bodyB->getVelocity().getLength()*.001),
								CallFunc::create(a, callfunc_selector(Player::resume)), 0));
							break;
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

		if((bodyA->getName() == "Projectile") && (bodyA->getTag() != bodyB->getTag()))
		{
			if(bodyB->getName() == "Player")
				for(auto &a : players)
					if(bodyB == a->getBody())
					{
						if(a->getDodge())
							return false;
						break;
					}

			return true;
		} else if((bodyA->getName() == "Projectile") && (bodyA->getTag() == bodyB->getTag()))
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


private:
	cocos2d::Director *director;
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
	Vector<Node*> pausedActions;
	//HUD Stuff Here
	cocos2d::Sprite* player1, *player2, *player3, *player4;
	cocos2d::Sprite* healthBar1, *healthBar2, *healthBar3, *healthBar4;
	cocos2d::Sprite* lives1, *lives2, *lives3, *lives4;
	vector<vector<Node*>> UIStuff;
	//HUD Stuff Ends

	double dtt = 0;

	int SET_SHAKE_DURATION;

	bool gamePaused = false;
	bool resumeBtnActive = false;
	bool restartBtnActive = false;
	bool quitBtnActive = false;

	bool countDown = true;
}; //Independance