#ifndef __HERO_H__
#define __HERO_H__
#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "definitions.h"
#include "Projectile.h"
#include <vector>
using namespace std;
class Hero : public cocos2d::Node
{
public:
	Hero(b2World* world,int x,int y);
	virtual ~Hero();
	void update(float delta);
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode key, cocos2d::Event* e);
	void onKeyRelease(cocos2d::EventKeyboard::KeyCode key, cocos2d::Event* e);
	void createBody();
	void fire();
	int i;
private:
	bool isLeft, isRight, isTop, isDown;
	b2Body* body;
	cocos2d::Sprite* sprite;
	cocos2d::Action* runnigAction;
	cocos2d::Animation* runAnim;
	b2World *world;
	int x, y;
	vector<Projectile*> guns;
};

#endif