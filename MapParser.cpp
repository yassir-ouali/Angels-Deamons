#include "MapParser.h"
#include "Hero.h"
#include "Ball.h"
using namespace std;
USING_NS_CC;

MapParser::MapParser(b2World* world)
{
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	//init world
	this->world = world;
	this->map = new TMXTiledMap;
	this->map->initWithTMXFile("mamap3.tmx");
	this->addChild(map,-1);
	this->instanceHero();
	instanceObstacles();
	instanceCoins();
	instanceHeaven();

}
void MapParser::instanceHero()
{
	TMXObjectGroup* heroLayer = map->getObjectGroup("hero");
	auto heroPos=heroLayer->getObject("hero");
	int x=heroPos["x"].asFloat();
	int y = heroPos["y"].asFloat();
	Hero* hero = new Hero(world, origin.x + x + map->getTileSize().width / 2, origin.y +( y + map->getTileSize().height / 2));
	this->addChild(hero,-1);
}
void MapParser::instanceObstacles()
{
	visibleSize = Director::getInstance()->getVisibleSize();
	TMXObjectGroup* obstacles = map->getObjectGroup("border");
	auto& obstacle = obstacles->getObjects();

	for (auto& obj : obstacle)
	{
		ValueMap& dict = obj.asValueMap();
		b2BodyDef bodyDef;
		float x = origin.x + dict["x"].asFloat() + dict["width"].asFloat() / 2;
		float y = origin.y + dict["y"].asFloat() + dict["height"].asFloat() / 2 ;
		bodyDef.position = b2Vec2(x,y);
		b2Body* body=world->CreateBody(&bodyDef);

		b2PolygonShape rect;
		rect.SetAsBox(dict["width"].asFloat()/2, dict["height"].asFloat()/2);

		b2FixtureDef fixtureDef;
		//fixtureDef.density.
		fixtureDef.shape = &rect;
		fixtureDef.friction = 0;
		body->CreateFixture(&fixtureDef);
		body->SetUserData("ooo");
	}
}
void MapParser::instanceCoins()
{
	auto white = map->getObjectGroup("white");
	for (auto& coin : white->getObjects())
	{
		ValueMap& dict = coin.asValueMap();
		float x = origin.x + dict["x"].asFloat() + dict["width"].asFloat() / 2;
		float y = origin.y + dict["y"].asFloat() + dict["height"].asFloat() / 2;
		Ball* w1 = new Ball(world, x, y, "white");
		this->addChild(w1);
		++Ball::score;
	}

	auto black = map->getObjectGroup("black");
	for (auto& coin : black->getObjects())
	{
		ValueMap& dict = coin.asValueMap();

		float x = origin.x + dict["x"].asFloat() + dict["width"].asFloat() / 2;
		float y = origin.y + dict["y"].asFloat() + dict["height"].asFloat() / 2;
		Ball* w2 = new Ball(world, x, y, "black");
		this->addChild(w2);
	}
}
void MapParser::instanceHeaven()
{
	auto white = map->getObjectGroup("heaven");
	for (auto& coin : white->getObjects())
	{
		ValueMap& dict = coin.asValueMap();
		float x = origin.x + dict["x"].asFloat() + dict["width"].asFloat() / 2;
		float y = origin.y + dict["y"].asFloat() + dict["height"].asFloat() / 2;
		Ball* w1 = new Ball(world, x, y, "heaven");
		this->addChild(w1);
	}
}

MapParser::~MapParser()
{
}