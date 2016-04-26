#ifndef __PROJECTLE_H__
#define __PROJECTLE_H__
#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "definitions.h"

class Projectile : public cocos2d::Node
{
public:
	Projectile(b2World* world, b2Body* body);
	virtual ~Projectile();
	void createBody();
	void setVisible(bool visible);
	void setSensor(bool sensor);
	void update(float dt);
	int j = 0;
	b2FixtureDef fixture;
	b2Body* body;
	bool collided=false;
private:
	b2Body* hero;
	cocos2d::Sprite* sprite;
	b2World *world;
};

#endif