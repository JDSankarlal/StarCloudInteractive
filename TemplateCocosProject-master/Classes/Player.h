#pragma once
#include <iostream>
#include <string>
#include "cocos2d.h"
#include "controller.h"
#include "SpriteAnimation.h"
#include "AudioPlayer.h";

using std::string;
USING_NS_CC;
using namespace Input;
class Player
{
public:

	Player(Scene *, int, int);
	~Player();
	PhysicsBody* getBody();
	Sprite* getSprite();
	Vec2 getVelocity();

#pragma region Set Velocities
	void setVelX(float);
	void setVelY(float);
	void setVel(float, float);
#pragma endregion

#pragma region Set Forces  
	void addForceX(float);
	void addForceY(float);
	void addForce(float, float);
#pragma endregion

//Player Movement

//must be called in update
	void movementUpdate(int controler);
//sets location by pixel position
	void setPosition(float x, float y, float z = 0);

	//get the position
	Vec2 getPosition();

	SpriteAnimation* getSpriteAnimater();

//sets the platform id
	void platformSwitch(int);

	void printInfo();
private:

	//Utility Function
	bool inRange(float,float,float);
	//Member Variables
	float LT, RT, movementPercent, lastMovement;
	bool dash;
	int initialDash;
	double moveZ, inst;
	bool jump;
	void platformID(int id);
	short colChange, jumpCount;
	bool hasJumped, colPress;
	int numJumps = 0, MaxHP, HP, lightDamage, heavyDamage, heavyDamageCharged, throwAttack, crossAttack;
	struct sfxPlayer
	{
		AudioPlayer* sfx = new AudioPlayer;
		string sounds[1] {"Audio/Heavy_Attack.mp3"};
	};

	Scene* scene;
	Sprite *AttachedSprite;
	Sprite* cursor[4] {Sprite::create("Assets/P1.png"), Sprite::create("Assets/P2.png"),
		Sprite::create("Assets/P3.png"), Sprite::create("Assets/P4.png")};

	PhysicsBody *body;
	SpriteAnimation* playerAni = new SpriteAnimation;
};

