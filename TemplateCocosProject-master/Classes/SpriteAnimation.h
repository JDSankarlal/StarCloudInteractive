#pragma once
#include <cocos2d.h>
#include <vector>
#include <string>
#include <filesystem>

USING_NS_CC;

using std::string;
using std::vector;
namespace fs = std::experimental::filesystem;

class SpriteAnimation
{
public:
	SpriteAnimation();
	~SpriteAnimation();

	//Adds a sprite to the animation list
	void addSprite(Sprite*);
	void addSprite(string directory);

	//Animates throught the vector of frames
	void animate(bool repeat = true);
	 //Pause
	void pause();
	//Resume
	void resume();
	//Restart
	void reset();
	//Remove
	void removeAllSprites();
	//Sets the animation speed in seconds 
	void setAnimationSpeed(float);

	Sprite* getSprite();
private:
	vector<string*> *frames = new vector<string*>;
	Sprite* frame = Sprite::create();
	clock_t* dt=new clock_t;
	Size* size = new Size();
	Vec2* position = new Vec2();
	int frameCounter;
	float fps;
	bool pauseAni=false;
};

