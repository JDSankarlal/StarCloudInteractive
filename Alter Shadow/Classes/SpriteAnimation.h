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

	//Sets the animation speed in seconds 
	void setAnimationSpeed(float);

	Sprite* getSprite();
private:
	vector<Sprite*> frames;
	Sprite* frame = Sprite::create();
	int frameCounter;
	clock_t dt;
	float fps;
	Size* size = new Size();
	Vec2* position = new Vec2();
};

