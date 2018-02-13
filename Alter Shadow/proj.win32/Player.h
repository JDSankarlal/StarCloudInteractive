#pragma once
#include <iostream>
#include <string>

using std::string;
class Player
{
	string playerIdentifier;
	int MaxHP, HP, lightDamage, heavyDamage, heavyDamageCharged, throwAttack, crossAttack;
public:
	Player(string _name);
	~Player();

};

