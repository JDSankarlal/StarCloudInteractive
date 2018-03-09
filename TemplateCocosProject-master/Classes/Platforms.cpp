#include "Platforms.h"
USING_NS_CC;

Platforms::Platforms(cocos2d::Scene *activeScene, int bitMask, bool shadow, float width, float height)
{
	//platform setup


	if(shadow)
	{
		platform = Sprite::create("pics/Shadow_Platform.png");
		child = Sprite::create("pics/Shadow_Platform_BG.png");
		child->setAnchorPoint(Vec2(0,.25));
		child->setScaleY(.98);
		platform->addChild(child);
	} else

		platform = Sprite::create("pics/Platform.png");



	   //sets the width and height of platform in pixles
	platform->setScaleX(width / platform->getContentSize().width);
	platform->setScaleY(height / platform->getContentSize().height);
	auto size = getSprite()->getContentSize();
	platform->setPhysicsBody(PhysicsBody::createBox(size));

	getBody()->setDynamic(false);
	getBody()->setCollisionBitmask(bitMask);
	activeScene->addChild(platform);

 //adds platform to active scene

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
//	if(child != nullptr)	child->setPosition3D(Vec3(x, y, z));
	
}

void Platforms::setVel(float x, float y)
{
	getBody()->setVelocity(Vec2(x, y));
}

void Platforms::update()
{
	platform->setPosition3D(position);
}
