#pragma once
#include <cocos2d.h>
USING_NS_CC;
class Projectial: public Node
{
public:
	Projectial(Scene * scene, int bitMask);
	~Projectial();

	PhysicsBody * getBody();
	Sprite* getSprite();

	void setSize(float);
	void setPosition(float x, float y, float z = 0);

#pragma region Set Velocities
	void setVelX(float);
	void setVelY(float);
	void setVel(float, float);
#pragma endregion
private:
	void removeProjectial();
	Sprite * proj=Sprite::create("Assets/light_attack.png");
	Scene* scene;
};

