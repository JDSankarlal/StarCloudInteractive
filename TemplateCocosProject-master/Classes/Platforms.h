#pragma once
#include "cocos2d.h"
class Platforms
{
public:
	/*
	 Descroption: creates platforms for players to stand on

	 Variables:
	  - ActiveScene = the parent scene that the platform will be added to.
	  - bitMask = determins which objects the colider checks. Only
	  objects with the same bitMask will be checked for collisions.
	  - shadow = used to check if a shadow platform will be created or a
	  normal one (but now we only use shadow platforms).
	  - width = the width of the platform
	  - height = the height of the platform
	*/
	Platforms(cocos2d::Scene* activeScene, int bitMask, bool shadow = true, float width = 200, float height = 100);
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

