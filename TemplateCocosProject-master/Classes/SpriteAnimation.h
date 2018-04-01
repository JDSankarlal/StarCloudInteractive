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

class SpriteAnimation:public Node
{
public:
	SpriteAnimation(Node * scene);
	~SpriteAnimation();

	//Adds a sprite to the animation list
	void addSprite(string,string directory);

	//Animates throught the vector of frames
	void update(float dt);
private:
	void animate();
public:
	//Sets wether to repeat the animation after the last frame is reached
	void setRepeat(bool);

	//Sets the animation speed in seconds 
	void setAnimationSpeed(float);
	
	//
	void setAnimation(string);

	//
	string getAnimation();

	//Restart
	void reset();

	string* getFolder();

	Sprite* getSprite();
private:
	unordered_map<string,vector<string*>*> *frames= new unordered_map<string, vector<string*>*>;
	string *folder = new string,ani;
	Sprite* frame = Sprite::create();
	clock_t* dt = new clock_t;
	Size* size = new Size();
	Vec2* position = new Vec2();
	int frameCounter;
	float fps;
	bool pauseAni = false, repeat;
};

