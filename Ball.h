#ifndef __BALL_H__
#define __BALL_H__
#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "definitions.h"

class Ball : public cocos2d::Node
{
public:
	Ball(b2World* world, int x, int y,char* c);
	virtual ~Ball();
	void update(float delta);
	void createBody();
	void createHeaven();
	void enterHeaven();
	void initScore();
	char* color="";
	static int score;
private:
	b2Body* body;
	cocos2d::Sprite* sprite;
	cocos2d::Action* runnigAction;
	cocos2d::Animation* runAnim;
	b2World *world;
	int x, y;
};

#endif