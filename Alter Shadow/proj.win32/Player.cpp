#pragma once 
#include "Player.h"


Player::Player(string _name, Scene *ActiveScene)
{
	auto AttachedSprite = Sprite::create("pics/test player.pngs");
	AttachedSprite->setScale(.3f);
	//AttachedSprite->setPosition(director->getOpenGLView()->getFrameSize().width / 2, director->getOpenGLView()->getFrameSize().height / 2);
	AttachedSprite->setPhysicsBody(PhysicsBody::create());
	ActiveScene->addChild(AttachedSprite);
	playerIdentifier = _name;
	MaxHP = 200;
	HP = 200;
	lightDamage = 5;
	heavyDamage = 7;
	heavyDamageCharged = 12;
	throwAttack = 5;
	crossAttack = 15;

}


Player::~Player()
{
}
