#include "Platforms.h"
USING_NS_CC;

Platforms::Platforms(cocos2d::Scene *activeScene, float width, float height)
{
	platform = Sprite::create("pics/Platform.png");
	platform->setScaleX(platform->getContentSize().width / width);
	platform->setScaleY(platform->getContentSize().height / height);
	platform->setPhysicsBody(PhysicsBody::create());
	activeScene->addChild(platform,0);
}

Platforms::~Platforms()
{}

void Platforms::setPosition(float x, float y, float z)
{
	platform->setPosition3D(Vec3(x, y, z));
}
