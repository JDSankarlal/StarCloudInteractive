#pragma once
#include <iostream>
#include <string>
#include "cocos2d.h"

using std::string;
using namespace cocos2d;
class Player
{
public:
	Player(Scene *);
	~Player();
	PhysicsBody* getBody();
	Sprite* getSprite();
	void setVelX(float);
	void setVelY(float);
	void setVel(float, float);

	void setPosition(float, float, float=0);
	void platformSwitch(int);
private:
	string playerIdentifier;
	Sprite *AttachedSprite;
	int MaxHP, HP, lightDamage, heavyDamage, heavyDamageCharged, throwAttack, crossAttack;
};

