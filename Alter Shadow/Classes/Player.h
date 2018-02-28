#pragma once
#include <iostream>
#include <string>
#include "cocos2d.h"
#include "controller.h"

using std::string;
using namespace cocos2d;
class Player
{
public:
//	enum
//	{
//		Players = 0x0001, //0000 0000 0000 0001
//		SolidPlatforms = 0x0002, //0000 0000 0000 0010
//		LucidPlatforms = 0x0004, //0000 0000 0000 0100
//		Hazards = 0x0008, //0000 0000 0000 1000
//		 //Category_05 = 0x0010, //0000 0000 0001 0000
//		 //Category_06 = 0x0020, //0000 0000 0010 0000
//		 //Category_07 = 0x0040, //0000 0000 0100 0000
//		 //Category_08 = 0x0080, //0000 0000 1000 0000
//		 //Category_09 = 0x0100; //0000 0001 0000 0000
//	};
	Player(Scene *);
	~Player();
	PhysicsBody* getBody();
	Sprite* getSprite();

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

//sets the platform id
	void platformSwitch(int);

	void printPosition();
private:
	float triggerL, triggerR;
	bool dash;
	int initialDash;
	double moveZ, inst;
	bool jump;
	void platformID(int id);
	string playerIdentifier;
	Sprite *AttachedSprite;
	bool hasJumped, colPress;
	short colChange, jumpCount;

	int MaxHP, HP, lightDamage, heavyDamage, heavyDamageCharged, throwAttack, crossAttack;
};

