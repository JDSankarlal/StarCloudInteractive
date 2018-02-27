#pragma once 
#include "Player.h"


Player::Player(Scene *ActiveScene)
{

	AttachedSprite = Sprite::create("pics/test player.png");
	AttachedSprite->setScale(1);
	auto size = getSprite()->getContentSize();
	getSprite()->setPhysicsBody(PhysicsBody::createBox(size));
	getBody()->setCollisionBitmask(1);

	getBody()->setDynamic(true);
	getBody()->setRotationEnable(false);
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

void Player::setVelX(float x)
{
	getBody()->setVelocity(Vec2(x, getBody()->getVelocity().y));
}

void Player::setVelY(float y)
{
	getBody()->setVelocity(Vec2(getBody()->getVelocity().x, y));
}

void Player::setVel(float x, float y)
{
	setVelX(x);
	setVelY(y);
}

void Player::addForceX(float x)
{
	getBody()->applyForce(Vec2(x, 0));
}

void Player::addForceY(float y)
{
	getBody()->applyForce(Vec2(0, y));
}

void Player::addForce(float x, float y)
{
	addForceX(x);
	addForceY(y);
}

void Player::setPosition(float x, float y, float z)
{
	getSprite()->setPosition3D(Vec3(x, y, 0));
	//getSprite()->setContentSize(Size());
	
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
	//platformID(platform+1);
}

void Player::platformID(int id)
{
	getBody()->setCollisionBitmask(id);
}

