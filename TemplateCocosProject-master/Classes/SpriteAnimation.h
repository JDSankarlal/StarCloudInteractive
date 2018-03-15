#pragma once
#include <cocos2d.h>
#include <vector>
#include <string>
#include <filesystem>
#include <unordered_map>

USING_NS_CC;

using std::string;
using std::vector;
using std::unordered_map;
namespace fs = std::experimental::filesystem;

class SpriteAnimation
{
public:
	SpriteAnimation();
	~SpriteAnimation();

	//Adds a sprite to the animation list
	void addSprite(string, string directory);

	//Animates throught the vector of frames
	void animate();

	//Sets wether to repeat the animation after the last frame is reached
	void setRepeat(bool);

	//Sets the animation speed in seconds 
	void setAnimationSpeed(float);

	void setBody(PhysicsBody*);

	//
	void setAnimation(string);

	//
	string getAnimation();

	//Pause
	void pause();

	//Resume
	void resume();

	//Restart
	void reset();

	string* getFolder();

	Sprite* getSprite();
private:
	unordered_map<string, vector<string>*> *frames=new unordered_map<string, vector<string>*>();
	PhysicsBody *pb;
	string *folder = new string, ani;
	Sprite* frame = Sprite::create(), *tmpFrame = Sprite::create();
	clock_t* dt = new clock_t;
	Size* size = new Size();
	Vec2* position = new Vec2();
	int frameCounter=0;
	float fps;
	bool pauseAni = false, repeat=true;
};

