#ifndef __MY_CONTACT_LISTENER_H__
#define __MY_CONTACT_LISTENER_H__
#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "definitions.h"

class MyContactListener : public b2ContactListener
{
public:
	MyContactListener();
	~MyContactListener();
	void BeginContact(b2Contact* contact);
private:
	cocos2d::TMXTiledMap* map;
	b2World* world;
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	bool started = false;
};

#endif