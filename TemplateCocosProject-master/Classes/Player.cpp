#pragma once 
#include "Player.h"
Player::Player(Scene *ActiveScene, int bitMask, int index)

{
	//Animation sets
	playerAni = new SpriteAnimation(this);
	playerAni->addSprite("walk", "Assets/Walk");
	playerAni->addSprite("jump", "Assets/Jump");
	playerAni->addSprite("dash", "Assets/Dash");
	playerAni->addSprite("heavy attack right", "Assets/Heavy_Attack_Right");
	playerAni->addSprite("light attack right", "Assets/Light_Attack_Right");
	playerAni->addSprite("light attack up", "Assets/Light_Attack_Up");

	//playerAni->addSprite("jump up", "Assets/Jump Up 2");
	//playerAni->addSprite("jump down", "Assets/Jump Down 2");
	//playerAni->addSprite("falling", "Assets/Falling");
	playerAni->setAnimation("walk");

	//Seting up the sprite and physics body
	AttachedSprite = playerAni->getSprite();
	getSprite()->setScale(.3);
	playerAni->setAnimationSpeed(.01);
	auto size = getSprite()->getContentSize();
	getSprite()->setPhysicsBody(PhysicsBody::createBox(size));
	getBody()->setName("Player");
	getBody()->setTag(index);
	getBody()->setCollisionBitmask(bitMask);
	getBody()->setContactTestBitmask(true);
	getBody()->setRotationEnable(false);

	cursor[index]->setAnchorPoint(Vec2(.5, 0));
	this->addChild(AttachedSprite, 2);
	this->addChild(cursor[this->index = index], 2);
	ActiveScene->addChild(this, 2);
	scene = ActiveScene;
	scheduleUpdate();
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

void Player::addImpulseX(float x)
{
	setVelX(0);
	getBody()->applyImpulse(Vec2(x, 0));
	//printf("Velx = %f\n", x);
}

void Player::addImpulseY(float y)
{
	setVelY(0);
	getBody()->applyImpulse(Vec2(0, y));
	//printf("Vely = %f\n", y);
}

void Player::addImpulse(float x, float y)
{
	addImpulseX(x);
	addImpulseY(y);
}

void Player::addImpulse(int x, int y)
{
	addImpulse(float(x), float(y));
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

void Player::update(float dt)
{

	movementUpdate();
}

void Player::movementUpdate()
{

	static Input::XBoxInput controllers;
	controllers.DownloadPackets(4);

	if(controllers.GetConnected(index))
	{
		if(!interupt())
		{
#pragma region Movement	
			//printInfo();
			Stick moveL, moveR;//left and right stick variables
			controllers.GetSticks(index, moveL, moveR);//inputs stick values
			static float lo = 0.f, hi = .001f;
			int move = 37500.f * 2.f * 1.25f;

			if(moveL.xAxis < 0)
				getSprite()->setFlippedX(fliped = true);
			else if(moveL.xAxis > 0)
				getSprite()->setFlippedX(fliped = false);

			if(moveL.yAxis < .8f)
				addImpulseX(move* moveL.xAxis);
			if(!dash)
				if(inRange(getVelocity().y, lo, hi))
				{
					if(moveL.xAxis != 0)
					{
						playerAni->resume();
						playerAni->setAnimationSpeed((1 - abs(moveL.xAxis)) * .001);
					} else
						playerAni->pause();
				}

#pragma endregion

#pragma region Jumping

			if((controllers.ButtonPress(index, A)) && (!hasJumped && numJumps < 2))
			{
				numJumps++;
				if(numJumps > 1)
					addImpulseY(53500.f * 5.f * numJumps * .75f);
				else
					addImpulseY(53500 * 5 * numJumps);
				hasJumped = true;
			} else
				if(controllers.ButtonRelease(index, A))
					hasJumped = false;
#pragma endregion

#pragma region Animation
			if(dash)
			{
				if(playerAni->getAnimation() != "dash")
				{
					OutputDebugStringA("Dash\n");
					playerAni->setRepeat(false);
					playerAni->setAnimation("dash");
					playerAni->setAnimationSpeed(.01);
				}
			} else if(inRange(getVelocity().y, -hi, hi))
			{
				if(playerAni->getAnimation() != "walk")
				{
					OutputDebugStringA("Walking\n");
					playerAni->setRepeat(true);
					playerAni->setAnimation("walk");
					playerAni->reset();
				}
			}

			//else if (getVelocity().y < 0.f && !inRange(getVelocity().y, -hi, lo))
			//{
			//	if (playerAni->getAnimation() != "falling")
			//	{
			//		OutputDebugStringA("Falling\n");
			//		playerAni->setRepeat(false);
			//		playerAni->setAnimation("falling");
			//		playerAni->setAnimationSpeed(.05);
			//		playerAni->reset();
			//	}
			//}
			else if(getVelocity().y > 0.f && !inRange(getVelocity().y, lo, hi))
			{
				if(playerAni->getAnimation() != "jump")
				{
					OutputDebugStringA("Jump\n");
					playerAni->reset();
					playerAni->setRepeat(false);
					playerAni->setAnimation("jump");
					playerAni->setAnimationSpeed(.01);

				}
			}
#pragma endregion

#pragma region Dash			
			controllers.GetTriggers(index, LT, RT);
			if(LT > .5 || RT > .5 && numDash < 1)
				controllers.SetVibration(index, LT, RT);
			if((LT > .5 || RT > .5) && !dash && numDash < 1)
			{
				numDash++;
				numJumps--;
				dash = true;
				initialDash = 1;
				if(move * 2 * initialDash * (moveL.xAxis / abs(moveL.xAxis)) != 0)
					addImpulseX(move * 2 * initialDash * (moveL.xAxis / abs(moveL.xAxis)));
			} else if(LT < .5 && RT < .5)
			{
				controllers.SetVibration(index, 0, 0);
				dash = false;
				playerAni->reset();
			}
			if(dash)
			{
				initialDash -= .001;
				if(move * 2 * initialDash * (moveL.xAxis / abs(moveL.xAxis)) > 0)
					addImpulseX(move * 2 * initialDash * (moveL.xAxis / abs(moveL.xAxis)));
				if(initialDash <= .5)
				{
					controllers.SetVibration(index, 0, 0);
				}
			}

#pragma endregion

#pragma region Attacks
			//static Projectile atk;
			if(controllers.ButtonStroke(index, Y) || controllers.ButtonStroke(index, B))
			{
				sfx->setAudio(sounds[0]);
				sfx->play();

				atk = new Projectile(scene, true, 1, index);

				atk->setSize(.5);
				atk->setPosition(getPosition().x, getPosition().y);

				if(moveL.yAxis > .8f)
				{
					atk->setRotation(90);
					atk->setVelY(500);
				} else if(!fliped)
				{
					atk->flipX(fliped);
					atk->setVelX(500);
				} else
				{
					atk->flipX(fliped);
					atk->setVelX(-500);
				}
			} else if(controllers.ButtonStroke(index, X))
			{
				sfx->setAudio(sounds[0]);
				sfx->play();

				atk = new Projectile(scene, false, 1, index);

				atk->setSize(.5);
				atk->setPosition(getPosition().x, getPosition().y);

				if(moveL.yAxis > .8f)
				{
					atk->setRotation(90);
					atk->setVelY(500);
				} else if(!fliped)
				{
					atk->flipX(fliped);
					atk->setVelX(500);
				} else
				{
					atk->flipX(fliped);
					atk->setVelX(-500);
				}
			}
#pragma endregion	
		}
#pragma region Cursor Location
		cursor[index]->setPosition(getSprite()->getPosition() +
								   Vec2(0, (getSprite()->getContentSize().height * getSprite()->getScaleY() / 2) + (cursor[index]->getContentSize().height*cursor[index]->getScaleY() / 2)));

		static Color3B colours2[] = {
			Color3B(1 * 255,0 * 255,0 * 255),//red
			Color3B(0 * 255,0 * 255,1 * 255),//blue
			Color3B(0 * 255,1 * 255,0 * 255),//green
			Color3B(1 * 255,1 * 255,0 * 255)};//yellow

		cursor[index]->setColor(colours2[index]);
#pragma endregion
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

void Player::printInfo()
{
	OutputDebugStringA(string("Player " + std::to_string(index) + ":\n").c_str());
	OutputDebugStringA(string("Position: " + std::to_string(getSprite()->getPosition().x) + ", " + std::to_string(getSprite()->getPosition().y) + "\n").c_str());
	OutputDebugStringA(string("Velocity: " + std::to_string(getBody()->getVelocity().x) + ", " + std::to_string(getBody()->getVelocity().y) + "\n").c_str());
	//OutputDebugStringA(string("Force: " + std::to_string(getBody()->getFirstShape()..x) + ", " + std::to_string(getBody()->getPosition().y) + "\n").c_str());
	OutputDebugStringA("\n\n");
}

void Player::resetJumps()
{
	numJumps = 0;
}

void Player::resetDashes()
{
	numDash = 0;
}

void Player::setDamage(int hp)
{
	damage = hp;
}

void Player::addDamage(int hp)
{
	damage += hp;
}

void Player::subtractDamage(int hp)
{
	damage -= hp;
}

int Player::getDamage()
{
	return damage;
}

int& Player::getLives()
{
	return lives;
}

void Player::setLives(int n)
{
	lives = n;
}

bool Player::inRange(float check, float low, float high)
{
	return check >= low && check <= high;
}