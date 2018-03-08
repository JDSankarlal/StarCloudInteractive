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
	void addSprite(const string directory);

	//Removes sprites from animation list
	void removeSprite();
	void removeAllSprites();

	//Animates throught the vector of frames
	void animate(const bool repeat = true);

	//Pause
	void pause();

	//Resume
	void resume();

	//Reset
	void reset();

	//Sets the animation speed in seconds 
	void setAnimationSpeed(const float);

	Sprite* getSprite();
private:
	vector<string*> *frames=new vector<string*>();
	Sprite* frame = Sprite::create(),frameTemp;
	clock_t dt;	  	
	Size* size = new Size();
	Vec2* position = new Vec2();
	bool pauseAni=false;
	float fps;
	int frameCounter;

};

