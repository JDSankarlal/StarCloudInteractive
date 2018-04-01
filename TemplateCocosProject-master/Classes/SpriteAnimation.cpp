#include "SpriteAnimation.h"

//USING_NS_CC;
//using std::string;
SpriteAnimation::SpriteAnimation(Node* scene)
{
	scene->addChild(this);
	this->scheduleUpdate();
}


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
	vector<string*>*vs = new vector<string*>;
	for(auto &a : fs::directory_iterator(directory))
	{
		OutputDebugStringA(cDir(a.path().string() + '\n').c_str());
		vs->push_back(new string(cDir(a.path().string())));
	}
	frames->insert({aniName,vs});

	frame->setTexture(*(*(*frames)[aniName])[0]); 
}

void SpriteAnimation::update(float dt)
{
	animate();
}

void SpriteAnimation::animate()
{
	//if(!pauseAni)
	//{
		float diffT = float(clock() - *dt) / CLOCKS_PER_SEC;
		if(diffT > fps)
		{
			if(((*frames)[ani])->size() > 0)
			{
				*dt = clock();
				frameCounter++;
			
				if(frameCounter >= ((*frames)[ani])->size() && repeat)
					frameCounter = 0;
				else if(frameCounter >= ((*frames)[ani])->size())
					frameCounter = ((*frames)[ani])->size() - 1;
			
				frame->setTexture(*(*(*frames)[ani])[frameCounter]);
				//frame->getPhysicsBody()->removeAllShapes();
				//frame->getPhysicsBody()->addShape(PhysicsShapeBox::create(frame->getContentSize()*frame->getScale()));
			}
		}
	//} else
	//	*dt = clock() - fps;
}

void SpriteAnimation::setRepeat(bool r)
{
	repeat = r;
}

string SpriteAnimation::getAnimation()
{
	return ani;
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

void SpriteAnimation::setAnimation(string aniName)
{
	ani = aniName;
	if((*frames)[ani] ->size()>0)
		frame->setTexture(*(*(*frames)[aniName])[0]);
}

Sprite* SpriteAnimation::getSprite()
{
	return frame;
}
