#pragma once
#include "cocos2d.h"
class Platforms
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
	Platforms(cocos2d::Scene*, int bitMask, bool shadow, float width = 200, float height = 100);
	~Platforms();
	cocos2d::Sprite* getSprite();
	cocos2d::PhysicsBody* getBody();

	void setPosition(float x, float y, float z = 0);
	void setVel(float x, float y);
	void update();//call each frame
private:
	bool state = false;
	cocos2d::Sprite* platform;
	cocos2d::Sprite* child;
	cocos2d::ParticleSystem* everything= cocos2d::ParticleExplosion::createWithTotalParticles(200);
	cocos2d::Vec3 position;
};

