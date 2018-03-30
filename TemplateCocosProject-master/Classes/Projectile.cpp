#include "Projectile.h"

Projectile::Projectile(Scene * scene, bool heavy, int bitMask, int index)
{
	proj[this->heavy = heavy]->setPhysicsBody(PhysicsBody::createCircle(0));

	getBody()->setGravityEnable(false);
	getBody()->setName("Projectile");
	getBody()->setTag(this->index = index);
	getBody()->setCollisionBitmask(this->bitMask = bitMask);
	getBody()->setContactTestBitmask(true);
	getBody()->setRotationEnable(false);
	addChild(proj[heavy]);
	scene->addChild(this);
	this->scene = scene;
	if(!heavy)
	{
		runAction(Sequence::create(DelayTime::create(1.3), CallFunc::create(this,
				  callfunc_selector(Projectile::removeProjectial)), 0));
	} else
	{
		runAction(Sequence::create(DelayTime::create(0.9), CallFunc::create(this,
				  callfunc_selector(Projectile::removeProjectial)), 0));
	}
}

Projectile::~Projectile()
{}

PhysicsBody * Projectile::getBody()
{

	return proj[heavy]->getPhysicsBody();
}

Sprite * Projectile::getSprite()
{
	return proj[heavy];
}

void Projectile::setSize(float scale)
{
	getBody()->removeAllShapes();
	proj[heavy]->setScale(scale);

	if(!heavy)
	{
		getBody()->addShape(PhysicsShapeCircle::create((proj[heavy]->getContentSize()).width / 2));
	} else
	{
		getBody()->addShape(PhysicsShapeCircle::create((proj[heavy]->getContentSize()).width / 8));
		getBody()->setPositionOffset(Vec2(proj[heavy]->getContentSize().width * scale * .25, 0));

	}
	getBody()->setName("Projectile");
	getBody()->setTag(index);
	getBody()->setCollisionBitmask(bitMask);
	getBody()->setContactTestBitmask(true);
}

void Projectile::setPosition(float x, float y, float z)
{
	proj[heavy]->setPosition3D(Vec3(x, y, z));
}

void Projectile::setVelX(float x)
{
	getBody()->setVelocity(Vec2(x, getBody()->getVelocity().y));
//	printf("Velx = %f\n", x);
}

void Projectile::setVelY(float y)
{
	getBody()->setVelocity(Vec2(getBody()->getVelocity().x, y));
//	printf("Vely = %f\n", y);
}

void Projectile::setVel(float x, float y)
{
	setVelX(x);
	setVelY(y);
}

void Projectile::flipX(bool flip)
{
	if(flip)
		getBody()->setPositionOffset(-getBody()->getPositionOffset());

	getSprite()->setFlippedX(flip);
}

void Projectile::flipY(bool flip)
{
	getSprite()->setFlippedY(flip);
}

void Projectile::setRotation(float deg)
{
	getBody()->setPositionOffset(Vec2(
		(proj[heavy]->getContentSize().width * getSprite()->getScale() * .25)*cos(deg * M_PI / 180),
		(proj[heavy]->getContentSize().width * getSprite()->getScale() * .25)*sin(deg * M_PI / 180)));
	getSprite()->setRotation(-deg);
}

void Projectile::removeProjectial()
{
	this->removeFromParent();
}


