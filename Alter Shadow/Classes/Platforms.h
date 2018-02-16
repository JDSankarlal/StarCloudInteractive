#pragma once
#include "cocos2d.h"
class Platforms
{
public:

	Platforms(cocos2d::Scene*,float=200,float=100);
	~Platforms();
	cocos2d::Sprite* getSprite();
	cocos2d::PhysicsBody* getBody();
	void setPosition(float,float,float=0);
	void update();//call each frame
private:

	bool state = false;
	cocos2d::Sprite* platform;
	cocos2d::Vec3 position;
};

