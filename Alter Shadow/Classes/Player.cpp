#pragma once 
#include "Player.h"

using namespace Input;
USING_NS_CC;

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

void Player::movementUpdate(int index)
{
	static XBoxInput controllers;
	controllers.DownloadPackets(index);


	if(controllers.GetConnected(index))
	{
		//OutputDebugStringA(string("Controller: "+std::to_string(index)+'\n').c_str());
#pragma region Movement	
		Stick moveL, moveR;

		controllers.GetSticks(index, moveL, moveR);
		int move = 375;

		if(moveL.xAxis != 0)
			lastMovement = moveL.xAxis;

		//Regular Movement
		movementPercent += .05f;

		if(moveL.xAxis == 0)
			movementPercent -= .15;
		else if(moveL.xAxis * move < 0)
			getSprite()->setFlippedX(true);
		else
			getSprite()->setFlippedX(false);

		if(movementPercent > 1)
			movementPercent = 1;
		else if(movementPercent < 0)
			movementPercent = 0;

		//setVelX(moveL.xAxis * move * movementPercent);
		//if(movementPercent > 0)
			setVelX(lastMovement*move * movementPercent);


#pragma region Jumping
		if((controllers.ButtonPress(index, A)) && !hasJumped)
		{
			setVelY(535);
			hasJumped = true;
		}
		if(controllers.ButtonRelease(index, A))
			hasJumped = false;
#pragma endregion

#pragma region Dash			
		controllers.GetTriggers(index, LT, RT);

		if((LT > .5 || RT > .5) && !dash)
		{
			controllers.SetVibration(index, 1, 1);
			dash = true;
			setVelY(0);
			initialDash = 800;
		} else if(LT < .5 && RT < .5)
		{
			controllers.SetVibration(index, 0, 0);
			dash = false;
		}
		if(dash)
		{
			if(initialDash > move)
			{
				if(moveL.xAxis < 0)
					setVelX(-(initialDash -= 20));
				else  if(moveL.xAxis > 0)
					setVelX(initialDash -= 20);
			} else
			{
				controllers.SetVibration(index, 0, 0);
			}
		}
#pragma endregion

#pragma endregion

#pragma region Switching Platforms
		//Dimentional colour change

		static Color3B colours[] {Color3B(1 * 255,1 * 255,1 * 255),Color3B(1 * 255,0 * 255,0 * 255),Color3B(0 * 255,1 * 255,1 * 255)};
		if(controllers.ButtonPress(index, LB) && !colPress)
		{
			colPress = true;
			if(colChange - 1 >= 0 && colChange - 1 < 3)
				getSprite()->setColor(colours[--colChange]);
		}


		if(controllers.ButtonPress(index, RB) && !colPress)
		{
			colPress = true;
			if(colChange + 1 >= 0 && colChange + 1 < 3)
				getSprite()->setColor(colours[++colChange]);
		}
		if(controllers.ButtonRelease(index, RB) && controllers.ButtonRelease(index, LB))
			colPress = false;
	//	platformSwitch(colChange);
#pragma endregion

	}

}

void Player::setPosition(float x, float y, float z)
{
	getSprite()->setPosition3D(Vec3(x, y, 0));
	//getSprite()->setContentSize(Size());

}

void Player::platformSwitch(int platform)
{


	if(inst < platform)
	{
		if(!jump)
		{
			jump = !jump;
			getBody()->setVelocity(Vec2(0, 350));

		}
		if(getBody()->getVelocity().y != 0)
			setPosition(getSprite()->getPosition().x, getSprite()->getPosition().y, moveZ += 1);
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
			setPosition(getSprite()->getPosition().x, getSprite()->getPosition().y, moveZ -= 1);
		else
			inst = platform;
	} else
	{
		jump = false;
	}
	//platformID(platform+1);
}

void Player::printPosition()
{
	OutputDebugStringA(string("Position: " + std::to_string(getSprite()->getPosition().x) + ", " + std::to_string(getSprite()->getPosition().y) + "\n").c_str());
}

void Player::platformID(int id)
{
	getBody()->setCollisionBitmask(id);
}

