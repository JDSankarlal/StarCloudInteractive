#include "Projectial.h"



Projectial::Projectial(Scene * scene, int bitMask)
{
	proj->setPhysicsBody(PhysicsBody::createCircle(proj->getContentSize().width / 2));
	getBody()->setGravityEnable(false);
	getBody()->setName("projectial");
	getBody()->setTag(bitMask);
	getBody()->setCollisionBitmask(bitMask);
	getBody()->setContactTestBitmask(true);
	getBody()->setRotationEnable(false);
	this->addChild(proj);
	
	//this->retain();
	scene->addChild(this);
	this->scene = scene;
	this->runAction(Sequence::create(DelayTime::create(3), CallFunc::create(this,
						   callfunc_selector(Projectial::removeProjectial)),0));
}

Projectial::~Projectial()
{}

PhysicsBody * Projectial::getBody()
{
	return proj->getPhysicsBody();
}

Sprite * Projectial::getSprite()
{
	return proj;
}

void Projectial::setSize(float scale)
{
	getBody()->removeAllShapes();
	proj->setScale(scale);
	getBody()->addShape(PhysicsShapeCircle::create((proj->getContentSize()).width / 2));
}

void Projectial::setPosition(float x, float y, float z)
{
	proj->setPosition3D(Vec3(x, y, z));
}

void Projectial::setVelX(float x)
{
	getBody()->setVelocity(Vec2(x, getBody()->getVelocity().y));
//	printf("Velx = %f\n", x);
}

void Projectial::setVelY(float y)
{
	getBody()->setVelocity(Vec2(getBody()->getVelocity().x, y));
//	printf("Vely = %f\n", y);
}

void Projectial::setVel(float x, float y)
{
	setVelX(x);
	setVelY(y);
}

void Projectial::removeProjectial()
{
	this->removeAllChildren();
	scene->removeChild(this);
	this->~Projectial();
}
