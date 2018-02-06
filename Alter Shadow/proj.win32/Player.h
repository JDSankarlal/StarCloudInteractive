#pragma once
#include <iostream>
#include <string>

using std::string;
class Player
{
	string playerIdentifier;
	int MaxHP, HP, lightDamage, heavyDamage, heavyDamageCharged, throwAttack, crossAttack;
public:
	Player(string _name)
	{
		playerIdentifier = _name;
		MaxHP = 200;
		HP = 200;
		lightDamage = 5;
		heavyDamage = 7;
		heavyDamageCharged = 12;
		throwAttack = 5;
		crossAttack = 15;
	};
	~Player();

};

