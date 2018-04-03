#pragma once
#include <iostream>
#include <string>
#include <functional>
#include "cocos2d.h"
#include "controller.h"
#include "SpriteAnimation.h"
#include "AudioPlayer.h"
#include "Projectile.h"

using namespace std;
USING_NS_CC;
using namespace Input;
class Player :public Node
{
public:
	/*
	Description: Initializes the player

	Variables:
	- parentScene = the scene to wich the player is attached.
	- bitMask = determins which objects the colider checks. Only
	objects with the same bitMask will be checked for collisions.
	- index = identifies which controller is moving the player as
	well as a differentiation between players.
	*/
	Player(Scene * ActiveScene, int bitMask, int index);

	~Player();

	//Gets the PhysicsBody* of the player
	PhysicsBody* getBody();
	//Gets the Sprite* of the player
	Sprite* getSprite();
	//Gets the velocity of the player as a Vec2
	Vec2 getVelocity();

#pragma region Set Velocity
	void setVelX(float x);
	void setVelY(float y);
	void setVel(float x, float y);
	template<class T> void setVel(T x, T y);
#pragma endregion


#pragma region Set Impulse
	void addImpulseX(float);
	void addImpulseY(float);
	void addImpulse(float, float);
	void addImpulse(int, int);

#pragma endregion

#pragma region Set Forces  
	void addForceX(float);
	void addForceY(float);
	void addForce(float, float);
#pragma endregion

//interupt inputs
	bool interupt(float dt)
	{

		if((interuptCounter += dt) / CLOCKS_PER_SEC > interuptCount)
			return false;
		bool con = interuptCounter / CLOCKS_PER_SEC < interuptCount;

		return con;

	}
	void setInterupt(float dt)
	{
		interuptCount = dt;
		interuptCounter = 0;
	}

//sets location of the player by pixel position
	void setPosition(float x, float y, float z = 0);

	//get the location of the player and returns it as a Vec2 
	Vec2 getPosition();

	void printInfo();

	void resetJumps();

	void resetDashes();

	void setDamage(int);

	void addDamage(int);

	void subtractDamage(int);

	int getDamage();

	int& getLives();

	void setLives(int n);

	bool getDodge();

	void setAttacking(bool);

private:
//Updates are called internaly, nolonger need to call them
	void update(float);
	void movementUpdate(float);
	bool inRange(float check, float low, float high);

	double moveZ, inst;
	float LT, RT, interuptCounter, interuptCount, initialDash;
	int  numJumps = 0, numDash = 0, damage = 0, lives = 3;
	short jumpCount, index;
	bool dash, hasJumped, fliped = false, dodge = false, attacking = false;

	AudioPlayer* sfx = new AudioPlayer;
	string sounds[1] {"Audio/NornieShot.mp3"};
	time_t* t = new time_t;
	Projectile *atk;
	Scene* scene;
	Sprite *AttachedSprite, *cursor[4] {Sprite::create("Assets/P1.png"),Sprite::create("Assets/P2.png"),Sprite::create("Assets/P3.png"),Sprite::create("Assets/P4.png")};
	SpriteAnimation* playerAni;
};

template<class T>
void Player::setVel(T x, T y)
{}
