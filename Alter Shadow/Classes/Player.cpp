#pragma once 
#include "Player.h"


Player::Player(Scene *ActiveScene)
{
	AttachedSprite = Sprite::create("pics/test player.png");
	AttachedSprite->setScale(.3f);
	auto size = getSprite()->getContentSize();
	getSprite()->setPhysicsBody(PhysicsBody::createBox(size));
	getBody()->setCollisionBitmask(1);
	getBody()->setContactTestBitmask(1);
	getBody()->setDynamic(true);
	ActiveScene->addChild(AttachedSprite);
	MaxHP = 200;
	HP = 200;
	lightDamage = 5;
	heavyDamage = 7;
	heavyDamageCharged = 12;
	throwAttack = 5;
	crossAttack = 15;

}


Player::~Player()
{}

PhysicsBody * Player::getBody()
{
	return AttachedSprite->getPhysicsBody();
}

Sprite * Player::getSprite()
{
	return AttachedSprite;
}

void Player::setVelX(float a_x)
{
	getBody()->setVelocity(Vec2(a_x, getBody()->getVelocity().y));
}

void Player::setVelY(float a_y)
{
	getBody()->setVelocity(Vec2(getBody()->getVelocity().x, a_y));
}

void Player::setVel(float a_x, float a_y)
{
	setVelX(a_x);
	setVelY(a_y);
}

void Player::setPosition(float x, float y, float z)
{
	getSprite()->setPosition3D(Vec3(x, y, z));
}

void Player::platformSwitch(int platform)
{
	static double move, inst;
	static bool jump;
	if(inst < platform)
	{
		if(!jump)
		{
			jump = !jump;
			getBody()->setVelocity(Vec2(0, 350));
		}
		if(getBody()->getVelocity().y != 0)
			setPosition(getSprite()->getPosition().x, getSprite()->getPosition().y, move += 1);
		else
			inst = platform;


	} else if(inst > platform)
	{
		if(!jump)
		{
			jump = !jump;
			getBody()->setVelocity(Vec2(0, 350));
		}
		if(getBody()->getVelocity().y != 0)
			setPosition(getSprite()->getPosition().x, getSprite()->getPosition().y, move -= 1);
		else
			inst = platform;

	} else
	{

		jump = false;
	}
}

