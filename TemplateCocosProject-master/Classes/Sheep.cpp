#include "Sheep.h"


Sheep::Sheep(Scene *ActiveScene, int bitMask)
{
	//sheepAni->addSprite("idle","Assets/FireSheep.png");
	//sheepAni->addSprite("walk", "Assets /FireSheep.png");
	//sheepAni->setAnimation("walk");
	AttachedSprite = Sprite::create("Assets/FireSheep.png");
	
	getSprite()->setScale(0.5);
	//sheepAni->setAnimationSpeed(.01);
	auto size = getSprite()->getContentSize();
	getSprite()->setPhysicsBody(PhysicsBody::createBox(size));
	getBody()->setTag(5);
	getBody()->setCollisionBitmask(bitMask);
	getBody()->setContactTestBitmask(true);
	getBody()->setDynamic(true);
	getBody()->setRotationEnable(false);
	getBody()->getFirstShape()->setFriction(.25);
	ActiveScene->addChild(AttachedSprite);
	MaxHP = 200;
	HP = 200;
}

Sheep::~Sheep()
{
}

PhysicsBody * Sheep::getBody()
{
	return AttachedSprite->getPhysicsBody();
}

Sprite * Sheep::getSprite()
{
	return AttachedSprite;
}

void Sheep::setPosition(float x, float y, float z)
{
	getSprite()->setPosition3D(Vec3(x, y, 0));
}

Vec2 Sheep::getPosition()
{
	return getSprite()->getPosition();
}

SpriteAnimation * Sheep::getSpriteAnimater()
{
	return sheepAni;
}

bool Sheep::onDeath()
{ 
	if (sheep1 == true)
	{
		setHP(200);
		setPosition(200, 300, 0);
		sheep1 = false;
	}
	else if (sheep1 == false && sheep2 == true)
	{
		sheep2 = false;
	}
	else return false;
}