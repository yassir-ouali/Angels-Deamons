#ifndef __START_SCENE_H__
#define __START_SCENE_H__

#include "cocos2d.h"

class Start : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
	// implement the "static create()" method manually
	CREATE_FUNC(Start);
private:
	void GoToGameScene(cocos2d::Ref *sender);
    
};

#endif
