#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "InputHandler.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
	//Create the actual scene object that gets used with the director. This function is called within AppDelegate.cpp 
	//'scene' is an autorelease object so we never have to call delete on it. If we did, your application would likely crash
	//Important note: Anytime you call ___::create() with Cocos2D, you will be getting an autoreleased object. You do not need to call delete on anything in the Cocos2D engine
	Scene* scene = Scene::createWithPhysics();



	//Create a layer that is going to be attached to the scene
	//This layer is what contains all of our objects since we are working within a DemoScene
	//Also, when we use 'this->' later on, this layer is what is being referred to
	HelloWorld* layer = HelloWorld::create();

	//Add the layer to the scene
	scene->addChild(layer);

	//Return the newly built scene
	//This is then passed to the director with director->runWithScene() or director->replaceScene() etc. In this case, director->runWithScene() is called in AppDelagate.cpp
	return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

	//VERY IMPORTANT LINE!
	//Allow for the update() function to be called by Cocos2D
	//Without this line, update() would NEVER be called. 
	//You can optionally add a schedule timing in here to explicity set an order for update calls. We do not need to do that, however
	//*** Forum Post: http://discuss.cocos2d-x.org/t/void-update-float-delta-is-not-executing/16614/4 ***//
	this->scheduleUpdate();

    return true;
}

void HelloWorld::update(float deltaTime)
{
	//Update the inputs so they are grabbed from the correct frame
	//This is a VERY IMPORTANT line of code. It ensures the inputs are updated and synced to the right frame
	//*** What happens if you remove this line of code? Try to run this scene without it! Hint: Try spawning birds! ***//
	INPUTS->clearForNextFrame();
}
