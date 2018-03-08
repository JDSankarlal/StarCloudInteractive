#pragma once
#include <cocos2d.h>
class EmptyScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	CREATE_FUNC(EmptyScene);
	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);
private:
	//cocos2d::Director *director;
};

