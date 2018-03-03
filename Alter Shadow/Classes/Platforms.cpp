#include "Platforms.h"
USING_NS_CC;

Platforms::Platforms(cocos2d::Scene *activeScene, int bitMask, float width, float height)
{
	//platform setup
	platform = Sprite::create("pics/Platform.png");

						 

	//sets the width and height of platform in pixles
	//if(width < platform->getContentSize().width)
	platform->setScaleX(width / platform->getContentSize().width);
//else
//	platform->setScaleX(1.f - platform->getContentSize().width / width);

//	if(height < platform->getContentSize().height)
	platform->setScaleY(height / platform->getContentSize().height);
//else
//	platform->setScaleY(1.f - platform->getContentSize().height / height);
	auto size = getSprite()->getContentSize();
	platform->setPhysicsBody(PhysicsBody::createBox(size));
	getBody()->setDynamic(false);
	getBody()->setCollisionBitmask(bitMask);
	//getBody()->setCategoryBitmask(2);

//	getBody()->setContactTestBitmask(1);
	
 //adds platform to active scene
	activeScene->addChild(platform);
}

Platforms::~Platforms()
{}

Sprite * Platforms::getSprite()
{
	return platform;
}

cocos2d::PhysicsBody * Platforms::getBody()
{
	return platform->getPhysicsBody();
}

void Platforms::setPosition(float x, float y, float z)
{
	platform->setPosition3D(Vec3(x, y, z));
}

void Platforms::setVel(float x,float y)
{
	getBody()->setVelocity(Vec2(x,y));
}

void Platforms::update()
{
	platform->setPosition3D(position);
}
