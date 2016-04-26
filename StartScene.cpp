using namespace std;
#include "StartScene.h"
#include "HelloWorldScene.h"
#include "definitions.h"
#include "cocos2d.h"
#include "Ball.h"
USING_NS_CC;

//extern int score;

Scene* Start::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
	auto layer = Start::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Start::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
	Ball::score = 0;
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto retryItem = MenuItemImage::create("start.png", "start.png", CC_CALLBACK_1(Start::GoToGameScene, this));
	retryItem->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2+origin.y));

	auto menu = Menu::create(retryItem, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu);
    return true;
}
void Start::GoToGameScene(cocos2d::Ref *sender)
{
	auto scene = HelloWorld::createScene();

	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}