#pragma once 
#include "Player.h"

Player::Player(Scene *ActiveScene, int bitMask,int index)
{
	playerAni->addSprite("walk", "Assets/Walk 2");
	playerAni->addSprite("jump up", "Assets/Jump Up 2");
	playerAni->addSprite("jump down", "Assets/Jump Down 2");
	playerAni->setAnimation("walk");
	AttachedSprite = playerAni->getSprite();
	getSprite()->setScale(.3);
	playerAni->setAnimationSpeed(.01);
	auto size = getSprite()->getContentSize();

	getSprite()->setPhysicsBody(PhysicsBody::createBox(size));
	getBody()->setTag(bitMask);
	getBody()->setCollisionBitmask(bitMask);
	getBody()->setContactTestBitmask(true);
	getBody()->setDynamic(true);
	getBody()->setRotationEnable(false);
	//getBody()->getFirstShape()->setFriction(.25);
	ActiveScene->addChild(AttachedSprite);

	scene = ActiveScene;
	ActiveScene->addChild(cursor[index]);


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

Vec2 Player::getVelocity()
{
	return getBody()->getVelocity();
}

void Player::setVelX(float x)
{
	getBody()->setVelocity(Vec2(x, getBody()->getVelocity().y));
	printf("Velx = %f\n", x);
}

void Player::setVelY(float y)
{
	getBody()->setVelocity(Vec2(getBody()->getVelocity().x, y));
	printf("Vely = %f\n", y);
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
	
	static Input::XBoxInput controllers;
	controllers.DownloadPackets(4);
	playerAni->animate();

	if(controllers.GetConnected(index))
	{

		//OutputDebugStringA(string("Controller: "+std::to_string(index)+'\n').c_str());
#pragma region Movement	
		Stick moveL, moveR;
		getBody()->getPosition();

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
		
			
		if(getVelocity().y == 0)
		{
			if(moveL.xAxis != 0)
			{
				playerAni->resume();
				playerAni->setAnimationSpeed((1.3 - abs(moveL.xAxis))*.1);
			} else
				playerAni->pause();
		}
		
		//getBody()->resetForces();
		
		//addForce(moveL.xAxis * 200000, 0);
		//printInfo();
#pragma region Jumping
		//OutputDebugStringA((std::to_string(numJumps) + '\n').c_str());
		if((controllers.ButtonPress(index, A)) && (!hasJumped && numJumps < 2))
		{
			numJumps++;
			setVelY(535);
			hasJumped = true;
		}
		if(controllers.ButtonRelease(index, A))
			hasJumped = false;

		if(getBody()->getVelocity().y > 0)
		{
			if(playerAni->getAnimation() != "jump up")
			{
				playerAni->setRepeat(false);
				playerAni->setAnimation("jump up");
				playerAni->reset();
			}
		} else if(getBody()->getVelocity().y < 0)
		{
			if(playerAni->getAnimation() != "jump down")
			{
				playerAni->setRepeat(false);
				playerAni->setAnimation("jump down");
				playerAni->reset();
			}
		} else
		{
			if(playerAni->getAnimation() != "walk")
			{
				playerAni->setRepeat(true);
				playerAni->setAnimation("walk");
				playerAni->reset();
			}
		}

#pragma endregion

#pragma region Dash			
		controllers.GetTriggers(index, LT, RT);

		if((LT > .5 || RT > .5) && !dash)
		{
			numJumps = 0;
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

#pragma region Attacks
		if(controllers.ButtonStroke(index, Y))
		{
			sfx->setAudio(sounds[0]);
			sfx->play();
		}
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
		cursor[index]->setPosition(getSprite()->getPosition() +
								   Vec2(0, (getSprite()->getContentSize().height * getSprite()->getScaleY() / 2) + (cursor[index]->getContentSize().height*cursor[index]->getScaleY() / 2)));

		static Color3B colours2[] = {Color3B(1 * 255,0 * 255,0 * 255),Color3B(0 * 255,0 * 255,1 * 255),Color3B(0 * 255,1 * 255,0 * 255),Color3B(1 * 255,0 * 255,1 * 255)};

		cursor[index]->setColor(colours2[index]);
		//getBody()->setVelocity(Vec2::ZERO);
	} else
	{
		cursor[index]->setPosition(-1 * (cursor[index]->getContentSize()));
	}

}

void Player::setPosition(float x, float y, float z)
{
	getSprite()->setPosition3D(Vec3(x, y, 0));
	//getSprite()->setContentSize(Size());
}

Vec2 Player::getPosition()
{
	return getSprite()->getPosition();
}

SpriteAnimation * Player::getSpriteAnimater()
{
	return playerAni;
}

void Player::platformSwitch(int platform)
{


	if(inst < platform)
	{
		if(!jump)
		{
			jump = !jump;
			setVel(0, 350);

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

void Player::printInfo()
{
	OutputDebugStringA(string("Player " + std::to_string(5) + ":\n").c_str());
	OutputDebugStringA(string("Position: " + std::to_string(getSprite()->getPosition().x) + ", " + std::to_string(getSprite()->getPosition().y) + "\n").c_str());
	OutputDebugStringA(string("Velocity: " + std::to_string(getBody()->getVelocity().x) + ", " + std::to_string(getBody()->getVelocity().y) + "\n").c_str());
	//OutputDebugStringA(string("Force: " + std::to_string(getBody()->getFirstShape()..x) + ", " + std::to_string(getBody()->getPosition().y) + "\n").c_str());
	OutputDebugStringA("\n\n");
}

void Player::platformID(int id)
{
	getBody()->setCollisionBitmask(id);
}

