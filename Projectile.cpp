#include "Projectile.h"
using namespace std;
USING_NS_CC;

Projectile::Projectile(b2World* world,b2Body *hero)
{
	//init world
	this->world = world;
	//inti body
	this->hero = hero;
	//init i for ref in the contact listner
	this->j = 5;
	//init the sprite with an image
	this->sprite = Sprite::create("ball.PNG");
	this->sprite->setScale(0.02f);
	this->addChild(sprite);
	scheduleUpdate();
	createBody();
}
void Projectile::createBody()
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_kinematicBody;
	body = world->CreateBody(&bodyDef);
	
	b2CircleShape circle;
	circle.m_radius =PROJECTILE_RADIUS;
	fixture.shape = &circle;
	fixture.filter.categoryBits = 0x001;
	fixture.filter.maskBits = 0x001;
	fixture.friction = 0;
	fixture.restitution = 1.0f;
	body->CreateFixture(&fixture);
	body->SetUserData(this);
	body->SetTransform(b2Vec2(hero->GetPosition().x + 20 * cos(hero->GetAngle()), hero->GetPosition().y + 20 * sin(hero->GetAngle())), hero->GetAngle());
	static int a = 1000;
	body->SetLinearVelocity(b2Vec2(a*cos(body->GetAngle()), a*sin(body->GetAngle())));
	a += 1000;

	
}
void Projectile::update(float dt)
{
	sprite->setPosition(Vec2(body->GetPosition().x, body->GetPosition().y));
}
void Projectile::setVisible(bool visible)
{
	sprite->setVisible(visible);
}
Projectile::~Projectile()
{
}
