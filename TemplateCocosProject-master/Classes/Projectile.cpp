#include "Projectile.h"

Projectile::Projectile(Scene * scene, bool heavy, int bitMask, int index)
{
	proj[0]->setPhysicsBody(PhysicsBody::createCircle(proj[0]->getContentSize().width / 2));
	getBody()->setGravityEnable(false);
	getBody()->setName("Projectile");
	getBody()->setTag(this->index = index);
	getBody()->setCollisionBitmask(this->bitMask = bitMask);
	getBody()->setContactTestBitmask(true);
	getBody()->setRotationEnable(false);
	addChild(proj[0]);
	scene->addChild(this);
	this->scene = scene;
	if(!(this->heavy=heavy))
	{ 
	
	runAction(act = Sequence::create(DelayTime::create(3), CallFunc::create(this,
			  callfunc_selector(Projectile::removeProjectial)), 0));
	} else
	{
		   runAction(act = Sequence::create(DelayTime::create(3), CallFunc::create(this,
			  callfunc_selector(Projectile::removeProjectial)), 0));
	}
}

Projectile::~Projectile()
{}

PhysicsBody * Projectile::getBody()
{

	return proj[0]->getPhysicsBody();
}

Sprite * Projectile::getSprite()
{
	return proj[0];
}

void Projectile::setSize(float scale)
{
	getBody()->removeAllShapes();
	proj[0]->setScale(scale);
	getBody()->addShape(PhysicsShapeCircle::create((proj[0]->getContentSize()).width / 2));
	getBody()->setName("Projectile");
	getBody()->setTag(index);
	getBody()->setCollisionBitmask(bitMask);
	getBody()->setContactTestBitmask(true);
}

void Projectile::setPosition(float x, float y, float z)
{

	proj[0]->setPosition3D(Vec3(x, y, z));
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

void Projectile::removeProjectial()
{
	//proj[0]->removeFromParent();  	
	this->removeFromParent();
}


