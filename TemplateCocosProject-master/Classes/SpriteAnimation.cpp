#include "SpriteAnimation.h"

USING_NS_CC;
using std::string;
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
		frames->push_back(new string(cDir(a.path().string())));
	}
	if(frames->size() > 0)
		frame->setTexture(*(*frames)[0]);
}

void SpriteAnimation::animate(bool repeat)
{
	if(!pauseAni)
	{			   
		float diffT = float(clock() - *dt) / CLOCKS_PER_SEC;
		if(diffT > fps)
		{
			if(frames->size() > 0)
			{
				*dt = clock();
				frameCounter++;
				if(frameCounter >= frames->size() && repeat)
					frameCounter = 0;
				else if(frameCounter >= frames->size())
					frameCounter--;

				frame->setTexture(*(*frames)[frameCounter]);

			}
		}
	} else
		*dt = clock()-fps;
}

void SpriteAnimation::pause()
{
	pauseAni = true;
}

void SpriteAnimation::resume()
{
	pauseAni = false;
}

void SpriteAnimation::reset()
{
	frameCounter = 0;
	if(frames->size() > 0)
		frame->setTexture(*(*frames)[0]);

}

void SpriteAnimation::removeAllSprites()
{
	for(auto &a : *frames)
		delete a;
	frames->clear();
}

void SpriteAnimation::setAnimationSpeed(float dt)
{
	this->fps = dt;
}

Sprite* SpriteAnimation::getSprite()
{
	return frame;
}
