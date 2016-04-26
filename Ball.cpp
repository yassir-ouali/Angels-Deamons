#include "Ball.h"
#include "math.h"
#include "StartScene.h"
using namespace std;
USING_NS_CC;

int Ball::score = 0;

Ball::Ball(b2World* world, int x, int y,char* c)
{
	//init world
	this->world = world;
	//init x and y
	this->x = x;
	this->y = y;
	//init color
	this->color = c;
	//create the body into the world
	if (color == "heaven")
	{
		createHeaven();
	}
	else
	{
		createBody();
	}
	
	//call update methode
	this->scheduleUpdate();

	
}
void Ball::createBody()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = b2Vec2(x, y);
	body = world->CreateBody(&bodyDef);
	b2CircleShape circle;
	circle.m_radius =BALL_RADIUS;
	b2FixtureDef bodyFixture;
	bodyFixture.shape = &circle;
	bodyFixture.filter.categoryBits = 0x001;
	bodyFixture.filter.maskBits = 0x001;
	bodyFixture.friction = 0;
	bodyFixture.restitution = 1.0f;

	if (color=="white")
	{
		body->SetLinearDamping(0.2f);
		//init the sprite with an image

		this->sprite = Sprite::create("1.png");
		this->sprite->setScale(0.1f);
		this->addChild(sprite);
		//animate
		runAnim = new Animation;
		runAnim->addSpriteFrameWithFile("1.png");
		runAnim->addSpriteFrameWithFile("2.png");
		runAnim->addSpriteFrameWithFile("3.png");
		runAnim->addSpriteFrameWithFile("4.png");
		runAnim->addSpriteFrameWithFile("5.png");
		runAnim->addSpriteFrameWithFile("6.png");
		runAnim->setDelayPerUnit(0.1f);
		runAnim->setLoops(-1);

		runnigAction = cocos2d::Animate::create(this->runAnim);
		runnigAction->setTag(1);
		sprite->runAction(cocos2d::Animate::create(this->runAnim));

	}

	else
	{
		this->sprite = Sprite::create("b1.png");
		this->sprite->setScale(0.1f);
		this->addChild(sprite);
		runAnim = new Animation;
		runAnim->addSpriteFrameWithFile("b1.png");
		runAnim->addSpriteFrameWithFile("b2.png");
		runAnim->addSpriteFrameWithFile("b3.png");
		runAnim->addSpriteFrameWithFile("b4.png");
		runAnim->addSpriteFrameWithFile("b5.png");
		runAnim->addSpriteFrameWithFile("b6.png");
		runAnim->setDelayPerUnit(0.1f);
		runAnim->setLoops(-1);

		runnigAction = cocos2d::Animate::create(this->runAnim);
		runnigAction->setTag(1);
		sprite->runAction(cocos2d::Animate::create(this->runAnim));

		body->SetLinearVelocity(b2Vec2(BLACK_BALL_SPEED*cos(50.0f), BLACK_BALL_SPEED*sin(50.0f)));
	}
	body->SetBullet(true);
	body->CreateFixture(&bodyFixture);
	body->SetUserData(this);
		
}
void Ball::createHeaven()
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position = b2Vec2(x, y);
	body = world->CreateBody(&bodyDef);
	b2CircleShape circle;
	circle.m_radius = BALL_RADIUS*4;
	b2FixtureDef bodyFixture;
	bodyFixture.shape = &circle;
	bodyFixture.filter.categoryBits = 0x001;
	bodyFixture.filter.maskBits = 0x001;
	bodyFixture.friction = 0;
	bodyFixture.isSensor = true;
	body->SetBullet(true);
	body->CreateFixture(&bodyFixture);
	body->SetUserData(this);
	
	this->sprite = Sprite::create("g1.png");
	this->sprite->setScale(0.2f);
	this->addChild(sprite);
	runAnim = new Animation;
	runAnim->addSpriteFrameWithFile("g1.png");
	runAnim->addSpriteFrameWithFile("g2.png");
	runAnim->addSpriteFrameWithFile("g3.png");
	runAnim->setDelayPerUnit(0.1f);
	runAnim->setLoops(-1);

	runnigAction = cocos2d::Animate::create(this->runAnim);
	runnigAction->setTag(1);
	sprite->runAction(cocos2d::Animate::create(this->runAnim));
}
void Ball::update(float delta)
{
	sprite->setPosition(Vec2(body->GetPosition().x, body->GetPosition().y));
	sprite->setRotation(-body->GetAngle() * 180 / 3.14f);
	if (score <= 0)
	{
		auto scene = Start::createScene();
		Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
	}
	if (color == "black" && body->GetLinearVelocity().x < BLACK_BALL_SPEED*cos(50.0f))
	{
		//body->SetLinearVelocity(b2Vec2(BLACK_BALL_SPEED*cos(-20.0f), BLACK_BALL_SPEED*sin(-20.0f)));
	}
}
void Ball::enterHeaven()
{
	sprite->setVisible(false);
}
Ball::~Ball()
{
}
