#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Hero.h"
#include "GLES-Render.h"
#include "MapParser.h"

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
	void initPhysics();
	virtual void draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform, uint32_t flags) override;
	void onDraw(const cocos2d::Mat4& transform, uint32_t flags);
	void update(float delta);
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

private:
	Hero* hero;
	b2Body* body;
	b2World* world;
	GLESDebugDraw debugDraw;
	//get rid of that after testing : draw and ondraw also !!
	cocos2d::CustomCommand _customCmd;
	cocos2d::Mat4 _modelViewMV;
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
