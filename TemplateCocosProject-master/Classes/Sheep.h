#pragma once
#include <iostream>
#include <string>
#include "cocos2d.h"
#include "SpriteAnimation.h"
#include "AudioPlayer.h";
#include "cocos2d.h"
#include "Player.h"
#include "Platforms.h"

using std::string;
USING_NS_CC;
//using namespace Input;
class Sheep
{
public:

	Sheep(Scene *ActiveScene, int bitMask);
	~Sheep();
	PhysicsBody* getBody();
	Sprite* getSprite();

	//get the position
	Vec2 getPosition();
	void setPosition(float x, float y, float z = 0);

	SpriteAnimation* getSpriteAnimater();

	bool onDeath();

	int getHP()
	{
		return HP;
	}
	int setHP(int n)
	{
		HP = n;
		return HP;
	}

	bool sheep1 = true;
	bool sheep2 = false;
	//sets the platform id
	//void printInfo();
private:

	int numJumps = 0, MaxHP, HP;
	struct sfxPlayer
	{
		//AudioPlayer* sfx = new AudioPlayer;
		//string sounds[1]{ "Audio/Heavy_Attack.mp3" };
	};

	Scene* scene;
	Sprite *AttachedSprite;
	PhysicsBody *body;
	SpriteAnimation* sheepAni = new SpriteAnimation;
	cocos2d::Sprite* sheepSprite;
};

