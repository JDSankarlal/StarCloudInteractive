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
	controllers.DownloadPackets();

//#pragma region Controller Stuff
	if(controllers.GetConnected(index))
	{
		OutputDebugStringA(string("Controller: "+std::to_string(index)+'\n').c_str());
#pragma region Movement	
		Stick moveL, moveR;

		controllers.GetSticks(index, moveL, moveR);
		int move = 375;
		//Regular Movement
		setVelX(moveL.xAxis * move);
		if(moveL.xAxis * move == 0)
			NULL;
		else if(moveL.xAxis * move < 0)
			getSprite()->setFlippedX(true);
		else
			getSprite()->setFlippedX(false);
#pragma region Jumping
		//Jumping
		if((controllers.ButtonPress(index, A)) && !hasJumped)
		{
			setVelY(535);
			hasJumped = true;
		}
		if(controllers.ButtonRelease(index, A))
			hasJumped = false;
#pragma endregion

		//Dash
		float triggerL, triggerR;
		controllers.GetTriggers(index, triggerL, triggerR);
		static bool dash;
		static int initialDash;
		if((triggerL > .5 || triggerR > .5) && !dash)
		{
			dash = true;
			setVelY(0);
			initialDash = 800;
		} else if(triggerL < .5 && triggerR < .5)
			dash = false;

		if(dash)
		{
			if(initialDash > move)
				if(moveL.xAxis < 0)
					setVelX(-(initialDash -= 20));
				else  if(moveL.xAxis > 0)
					setVelX(initialDash -= 20);
		}

#pragma endregion
//	   
//#pragma region Switching Platforms
//		//Dimentional colour change
//		
//		//Color3B colours[] {Color3B(1 * 255,1 * 255,1 * 255),Color3B(1 * 255,0 * 255,0 * 255),Color3B(0 * 255,1 * 255,1 * 255)};
//		//if(controllers.ButtonPress(controller, LB) && !colPress)
//		//{
//		//	colPress = true;		 
//		//	if(colChange - 1 >= 0 && colChange - 1 < 3)
//		//		getSprite()->setColor(Color3B(colours[--colChange])); 
//		//}
//		//
//		//
//		//if(controllers.ButtonPress(controller, RB) && !colPress)
//		//{
//		//	colPress = true;
//		//	if(colChange + 1 >= 0 && colChange + 1 < 3)
//		//		getSprite()->setColor(Color3B(colours[++colChange]));
//		//}
//		//if(controllers.ButtonRelease(controller, RB) && controllers.ButtonRelease(controller, LB))
//		//	colPress = false;
//	//	platformSwitch(colChange);
//#pragma endregion
	
	}
#pragma endregion
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

void Player::printPosition()
{
	OutputDebugStringA(string("Position: "+std::to_string(getSprite()->getPosition().x)+", "+ std::to_string(getSprite()->getPosition().y)+"\n").c_str());
}

void Player::platformID(int id)
{
	getBody()->setCollisionBitmask(id);
}

