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

	/*
	Description:
	Adds a sprite to the animation list given an alias and a file directory.
	Takes all images from directory.
	
	 Peramitors:
	 * alias - the alias given to the animation.
	 * directory - the file directory where the sprites are heald.
	*/ 
	void addSprite(string alias,string directory);

	//Animates throught the vector of frames
	void update(float dt);

private:
	//see update(float dt);
	void animate(float dt);
public:
	//Sets wether to repeat the animation after the last frame is reached
	void setRepeat(bool rep);

	//Sets the animation speed in seconds 
	void setAnimationSpeed(float aniSpeed);
	
	/*Sets which animation plays based on the aliases given in
	addSprite();.

	see, addSprite(string alias,string directory);
	 */
	void setAnimation(string alias);

	//Gets the alias given to the animation
	string getAnimation();

	//Restart
	void reset();

	//Gets the pointer to the Sprite variable
	Sprite* getSprite();
private:
	unordered_map<string,vector<string*>*> *frames= new unordered_map<string, vector<string*>*>;
	string ani;
	Sprite* frame = Sprite::create();
	//clock_t* dt = new clock_t;
	Size* size = new Size();
	Vec2* position = new Vec2();
	int frameCounter;
	float fps;
	bool pauseAni = false, repeat;
};

