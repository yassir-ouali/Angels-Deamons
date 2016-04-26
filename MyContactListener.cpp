using namespace std;
#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "MyContactListener.h"
#include "MapParser.h"
#include "Hero.h"
#include "Ball.h"
#include "Projectile.h"
#include "GameOverScene.h"
USING_NS_CC;

MyContactListener::MyContactListener()
{

}
void MyContactListener::BeginContact(b2Contact* contact)
{
	b2Body* bodyA = contact->GetFixtureA()->GetBody();
	b2Body* bodyB = contact->GetFixtureB()->GetBody();

	std::string c_white("white");

	Hero* h1 = static_cast<Hero*>(bodyA->GetUserData());
	Hero* h2 = static_cast<Hero*>(bodyB->GetUserData());

	Ball* b1 = static_cast<Ball*>(bodyA->GetUserData());
	Ball* b2 = static_cast<Ball*>(bodyB->GetUserData());

	if ((h1 != NULL && b2->color == "white")/* || (h2 != nullptr && b1->color!=NULL)*/)
	{
		if (h1->i == 2)
		{
			log("white ball");
		}
	}

	if ((h1 != NULL && b2->color == "black"))
	{
		if (h1->i == 2)
		{
			log("black ball");
			auto scene = GameOver::createScene();
			Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
		}
	}

	if (b2 != NULL && b1 != NULL && b2->color == "black" && b1->color == "white")
	{
		auto scene = GameOver::createScene();
		Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
		/*
		if (started)
		{
			auto scene = GameOver::createScene();
			
		}
		else
		{
			started = true;
		}*/

	}

	if (b2 != NULL && b1 != NULL && b2->color == "heaven" && b1->color == "white")
	{
		b1->enterHeaven();
		b2Filter filter;
		filter.categoryBits = 0x100;
		filter.maskBits = 0x100;
		bodyA->GetFixtureList()->SetFilterData(filter);
		Ball::score--;

	}

	Projectile* p1 = (Projectile*)(bodyA->GetUserData());
	Projectile* p2 = (Projectile*)(bodyB->GetUserData());
	if (p1)
	{
		if (p1->j == 5)
		{
			log("fire detetcted");
			p1->collided = true;
		}
	}

	if (p2)
	{
		if (p2->j == 5)
		{
			log("fire detetcted");
			p2->collided = true;
		}
	}
}
MyContactListener::~MyContactListener()
{

}