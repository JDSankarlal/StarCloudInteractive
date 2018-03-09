#pragma once
#include <cocos2d.h>
#include <vector>
#include <string>
#include <filesystem>

USING_NS_CC;

using namespace std;
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

	//pause
	void pause();
	//Resume
	void resume();
	//Remove
	void removeAllSprites();
	//Reset
	void reset();
	//Sets the animation speed in seconds 
	void setAnimationSpeed(float);

	Sprite* getSprite();
private:
	vector<string*> *frames = new vector<string*>;
	Sprite* frame = Sprite::create();
	clock_t dt;
	Size* size = new Size();
	Vec2* position = new Vec2();
	bool pauseAni=false;
	float fps;
	int frameCounter;
};

