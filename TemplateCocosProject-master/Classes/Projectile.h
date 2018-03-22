#pragma once
#include <cocos2d.h>
USING_NS_CC;
class Projectile : public Node
{
public:
	Projectile(Scene * scene, bool heavy, int bitMask, int index);
	~Projectile();

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
	bool heavy;
	int bitMask, index;
	Sprite * proj[2] {Sprite::create("Assets/light_attack.png"),Sprite::create("Assets/heavy_attack.png")};
	Scene* scene;
	Action* act;
};

