#include "Hero.h"
#include "math.h"
using namespace std;
USING_NS_CC;

Hero::Hero(b2World* world,int x,int y)
{
	//init world
	this->i = 2;
	this->world = world;
	//init x and y
	this->x = x;
	this->y = y;
	//init the sprite with an image
	this->sprite = Sprite::create("bar.PNG");
	//sprite->setPosition(Vec2(120.0f, 120.0f));
	sprite->setScale(0.2f);
	
	this->addChild(sprite);
	//init the boolean attribute
	isLeft =isRight = isTop= isDown = false;

	//check input
	auto eventListener = EventListenerKeyboard::create();
	eventListener->onKeyPressed = CC_CALLBACK_2(Hero::onKeyPressed, this);
	eventListener->onKeyReleased = CC_CALLBACK_2(Hero::onKeyRelease, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventListener, this);
	//call update methode
	this->scheduleUpdate();

	//create the body into the world
	createBody();
}
void Hero::createBody()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = b2Vec2(x,y);
	body = world->CreateBody(&bodyDef);

	b2PolygonShape rect;
	rect.SetAsBox(10.0f,40.0f);
	b2FixtureDef bodyFixture;
	bodyFixture.shape = &rect;
	bodyFixture.friction = 0;
	bodyFixture.restitution = 1.0f;
	bodyFixture.filter.categoryBits = 0x001;
	bodyFixture.filter.maskBits = 0x001;
	body->CreateFixture(&bodyFixture);
	body->SetUserData(this);
}
void Hero::onKeyPressed(cocos2d::EventKeyboard::KeyCode key, cocos2d::Event* e)
{
	if (cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW == key)
	{
		if (!isLeft){
			isRight = true;
			body->SetAngularVelocity(-SPEED_ROTATE);
		}
	}
	if (cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW == key)
	{
		if (!isRight)
		{
			isLeft = true;
			body->SetAngularVelocity(SPEED_ROTATE);
		}
	}
	if (cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW == key)
	{
		if (!isDown)
		{
			isTop = true;

		}
	}
	if (cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW == key)
	{
		if (!isTop)
		{
			isDown = true;
			//body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x, -SPEED_HERO));
		}
	}

	//fire
	if (cocos2d::EventKeyboard::KeyCode::KEY_SPACE == key)
	{
		fire();
	}
}
void Hero::onKeyRelease(cocos2d::EventKeyboard::KeyCode key, cocos2d::Event* e)
{
	if (cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW == key)
	{
		if (!isLeft){
			body->SetAngularVelocity(0);
			isRight = false;
		}
			
	}
	if (cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW == key)
	{
		if (!isRight){
			body->SetAngularVelocity(0);
			isLeft = false;
		}
			
	}
	if (cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW == key)
	{
		if (!isDown){
			body->SetLinearVelocity(b2Vec2(0, 0));
			isTop = false;
		}
			
	}
	if (cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW == key)
	{
		if (!isTop){
			//body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x, 0));
			isDown = false;
		}
			
	}
}
void Hero::fire()
{
	Projectile* p = new Projectile(world, body);
	this->addChild(p);
	guns.push_back(p);
}
void Hero::update(float delta)
{
	sprite->setPosition(Vec2(body->GetPosition().x, body->GetPosition().y));
	sprite->setRotation(-body->GetAngle() * 180 / 3.14f);

	if (isTop){
		body->SetLinearVelocity(b2Vec2(SPEED_HERO*cos(body->GetAngle()), SPEED_HERO*sin(body->GetAngle())));
	}
	else
	{
		body->SetLinearVelocity(b2Vec2(0.0f,0.0f));
	}
	
	for (vector<Projectile*>::iterator i = guns.begin(); i != guns.end(); i++)
	{
		if ((*i)->collided)
		{
			(*i)->fixture.isSensor = true;
			//delete (*i);
			//guns.erase(i);
			break;
		}
	}
}
Hero::~Hero()
{
}
