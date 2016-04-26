using namespace std;
#include "HelloWorldScene.h"
#include "MapParser.h"
#include "MyContactListener.h"
#include "Ball.h"
#include "SimpleAudioEngine.h"
#include "cocos2d.h"
USING_NS_CC;
using namespace CocosDenshion;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	auto backgroundSprite = Sprite::create("background5.png");
	backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(backgroundSprite);

	initPhysics();
	scheduleUpdate();

	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("funny_ghost.mp3");
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("funny_ghost.mp3", true);
	return true;
}

void HelloWorld::initPhysics(){
	world = new  b2World(b2Vec2(GRAVITY_X, GRAVITY_Y));
	world->SetAllowSleeping(true);
	world->SetContinuousPhysics(true);
	MapParser* map = new MapParser(world);
	//map->setOpacity(20);
	this->addChild(map, 0);
	world->SetDebugDraw(&debugDraw);
	uint32 flags = 0;
	flags += b2Draw::e_shapeBit;
	// flags += b2Draw::e_jointBit;
	// flags += b2Draw::e_aabbBit;
	// flags += b2Draw::e_pairBit;
	debugDraw.SetFlags(flags);
	MyContactListener* listener=new MyContactListener();
	world->SetContactListener(listener);

}
void HelloWorld::onDraw(const cocos2d::Mat4& transform, uint32_t flags){
	Director* director = Director::getInstance();
	CCASSERT(nullptr != director, "Director is null when seting matrix stack");
	director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
	director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, transform);

	GL::enableVertexAttribs(cocos2d::GL::VERTEX_ATTRIB_FLAG_POSITION);
	//m_test->Step(&settings);
	world->DrawDebugData();
	CHECK_GL_ERROR_DEBUG();

	director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
}

void HelloWorld::draw(cocos2d::Renderer* renderer, const cocos2d::Mat4 &transform, uint32_t flags)
{
	Layer::draw(renderer, transform, flags);

	_customCmd.init(_globalZOrder, transform, flags);
	_customCmd.func = CC_CALLBACK_0(HelloWorld::onDraw, this, transform, flags);
	renderer->addCommand(&_customCmd);
}
void HelloWorld::update(float dt)
{
	world->Step(1.0f/60, VELOCITY_STEP, 1);
}
void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
