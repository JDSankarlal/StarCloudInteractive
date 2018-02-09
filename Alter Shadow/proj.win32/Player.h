#pragma once
#include <iostream>
#include <string>
#include "cocos2d.h"

using std::string;
using namespace cocos2d;
class Player
{
	string playerIdentifier;
	int MaxHP, HP, lightDamage, heavyDamage, heavyDamageCharged, throwAttack, crossAttack;
public:
	Player(string, Scene *);
	~Player();
private:
};

