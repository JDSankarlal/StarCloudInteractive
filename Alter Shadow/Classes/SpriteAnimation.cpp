#include "SpriteAnimation.h"

USING_NS_CC;

SpriteAnimation::SpriteAnimation()
{}


SpriteAnimation::~SpriteAnimation()
{}

void SpriteAnimation::addSprite(Sprite * sprite)
{

}
string cDir(string dir)
{
	for(auto &a : dir)
		if(a == '\\')
			a = '/';
	return dir;
}
void SpriteAnimation::addSprite(string directory)
{
	//int count=0;
	for(auto &a : fs::directory_iterator(directory))
	{
		OutputDebugStringA(cDir(a.path().string() + '\n').c_str());
		frames.push_back(Sprite::create(cDir(a.path().string())));
	}
}

void SpriteAnimation::animate(bool repeat)
{
	float diffT = (clock() - dt) / CLOCKS_PER_SEC;
	if(diffT > fps)
	{
		if(frames.size() > 0)
		{
			dt = clock();
			frameCounter++;
			if(frameCounter >= frames.size() && repeat)
				frameCounter = 0;
			else if(frameCounter >= frames.size())
				frameCounter--;

			frame->setTexture(frames[frameCounter]->getTexture()->getPath());
			//frame->setScaleX(size->width);
			//frame->setScaleY(size->height);
			//frame->setPosition(*position);
			//*size = Size(frame->getScaleX(), frame->getScaleY());
			//*position = frame->getPosition();
		}
	}
}

void SpriteAnimation::setAnimationSpeed(float dt)
{
	this->dt = dt;
}

Sprite* SpriteAnimation::getSprite()
{
	return frame;
}
