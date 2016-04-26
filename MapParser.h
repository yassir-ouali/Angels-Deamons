#ifndef __MAP_PARSER_H__
#define __MAP_PARSER_H__
#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "definitions.h"

class MapParser : public cocos2d::Node
{
public:
	MapParser(b2World* world);
	virtual ~MapParser();
	void instanceHero();
	void instanceObstacles();
	void instanceCoins();
	void instanceHeaven();
	cocos2d::TMXTiledMap* map;
private:
	b2World* world;
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
};

#endif