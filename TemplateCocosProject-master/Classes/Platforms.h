#pragma once
#include "cocos2d.h"
class Platforms
{
public:

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
	cocos2d::Vec3 position;
};

