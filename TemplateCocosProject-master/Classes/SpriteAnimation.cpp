#include "SpriteAnimation.h"

//USING_NS_CC;
//using std::string;
SpriteAnimation::SpriteAnimation()
{}


SpriteAnimation::~SpriteAnimation()
{}


string cDir(string dir)
{
	for(auto &a : dir)
		if(a == '\\')
			a = '/';
	return dir;
}
void SpriteAnimation::addSprite(string aniName, string directory)
{
	*folder = directory;
	vector<string>*vs = new vector<string>();
	for(auto &a : fs::directory_iterator(directory))
	{
		OutputDebugStringA(cDir(a.path().string() + '\n').c_str());
		vs->push_back(cDir(a.path().string()));
	}
	frames->insert({aniName,vs});

	frame->setTexture(frames->at(aniName)->at(0));	
}

void SpriteAnimation::animate()
{
	if(!pauseAni)
	{
		float diffT = float(clock() - *dt) / CLOCKS_PER_SEC;
		if(diffT > fps)
		{
			if(frames->at(ani)->size() > 0)
			{
				*dt = clock();
				frameCounter++;
				if(frameCounter >= (frames->at(ani)->size()) && repeat)
					frameCounter = 0;
				else if(frameCounter >= (frames->at(ani)->size()))
					frameCounter = frames->at(ani)->size() - 1;
			//	OutputDebugStringA();
				frame->setTexture(frames->at(ani)->at(frameCounter));
				//frame->initWithFile(frames->at(ani).at(frameCounter));
				OutputDebugStringA("Things are not working\n\n");
				//tmpFrame = Sprite::create(*(*(*frames)[ani])[frameCounter]);
				//frame = Sprite::create((*frames)[ani][frameCounter]);

				//tmpFrame->setPhysicsBody(frame->getPhysicsBody());
				//frame = tmpFrame;
				//Director::getInstance()->getRunningScene()->addChild(frame);
			}
		}
	} else
		*dt = clock() - fps;
}

void SpriteAnimation::setRepeat(bool r)
{
	repeat = r;
}

string SpriteAnimation::getAnimation()
{
	return ani;
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
}

string * SpriteAnimation::getFolder()
{
	return folder;
}

void SpriteAnimation::setAnimationSpeed(float dt)
{
	this->fps = dt;
}

void SpriteAnimation::setBody(PhysicsBody* body)
{
	pb = body;
}

void SpriteAnimation::setAnimation(string aniName)
{
	ani = aniName;
	
	//auto a=((frames)->at(ani).at(0));
	frame->setTexture(frames->at(ani)->at(0));  //Problem is that texture scrolling is incorrect
}

Sprite* SpriteAnimation::getSprite()
{
	return frame;
}
