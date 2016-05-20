#include "HelloWorldScene.h"

using namespace std;
USING_NS_CC;

namespace {
    const int TagTint = 5;
    const int TagAnimate = 6;
}

HelloWorld::HelloWorld()
:_sprite(nullptr),
_tint(false),
_direction(South)
{}

HelloWorld::~HelloWorld()
{}

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

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto tint = MenuItemLabel::create(Label::createWithSystemFont("Tint", "arial", 30),
                                      CC_CALLBACK_1(HelloWorld::tintButtonPressed, this));
    tint->setAnchorPoint(Vec2::ZERO);
    tint->setPosition(origin);
    
    auto color = MenuItemLabel::create(Label::createWithSystemFont("Set Color", "arial", 30),
                                       CC_CALLBACK_1(HelloWorld::setColorButtonPressed, this));
    color->setAnchorPoint(Vec2::ZERO);
    color->setPosition(origin +  Vec2(0, 40));

    // create menu, it's an autorelease object
    auto menu = Menu::create(tint, color, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    _sprite = Sprite::createWithSpriteFrameName("RRGPlayer/toumei.png");
    _sprite->setPosition(origin + visibleSize / 2);
    addChild(_sprite, 10);
    
    runAnimate(South);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}

void HelloWorld::tintButtonPressed(cocos2d::Ref* sender)
{
    CCLOG("%s", __PRETTY_FUNCTION__);
    _sprite->stopActionByTag(TagTint);
    
    if (!_tint) {
        TintTo* tint = TintTo::create(.3f, 100, 0, 100);
        TintTo* tintReverse = TintTo::create(.3f, 150, 0, 150);
        Sequence* tintSeq = Sequence::createWithTwoActions(tint, tintReverse);
        RepeatForever* repeat = RepeatForever::create(tintSeq);
        repeat->setTag(TagTint);
        _sprite->runAction(repeat);
        _tint = true;
    } else {
        _sprite->setColor(Color3B::WHITE);
        _tint = false;
    }
}
void HelloWorld::setColorButtonPressed(cocos2d::Ref* sender)
{
    CCLOG("%s", __PRETTY_FUNCTION__);
    _sprite->stopActionByTag(TagTint);
    
    if (!_tint) {
        _sprite->setColor(Color3B::ORANGE);
        _tint = true;
    } else {
        _sprite->setColor(Color3B::WHITE);
        _tint = false;
    }
}

void HelloWorld::runAnimate(const Vec2& direction)
{
    float delay = .1f;
    int frameCount = 4;
    
    string directionStr = "";
    if (direction == North) {
        directionStr = "north";
    } else if (direction == NorthEast) {
        directionStr = "northeast";
    } else if (direction == East) {
        directionStr = "east";
    } else if (direction == SouthEast) {
        directionStr = "southeast";
    } else if (direction == South) {
        directionStr = "south";
    } else if (direction == SouthWest) {
        directionStr = "southwest";
    } else if (direction == West) {
        directionStr = "west";
    } else if (direction == NorthWest) {
        directionStr = "northwest";
    }
    
    Animation* animation = Animation::create();
    for (int i = 1; i <= frameCount; i++) {
        animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("RRGPlayer/walk/%s/%04d.png",directionStr.c_str(),i)));
    }
    animation->setDelayPerUnit(delay);
    
    Animate* animate = Animate::create(animation);
    RepeatForever* repeat = RepeatForever::create(animate);
    repeat->setTag(TagAnimate);
    
    _sprite->stopActionByTag(TagAnimate);
    _sprite->runAction(repeat);
}

bool HelloWorld::onTouchBegan(Touch* touch, Event* event)
{
    return true;
}
void HelloWorld::onTouchMoved(Touch* touch, Event* event)
{
    return;
}
void HelloWorld::onTouchEnded(Touch* touch, Event* event)
{
    int range = 50;
    Vec2 localPos = convertTouchToNodeSpace(touch);
    Vec2 v = localPos - _sprite->getPosition();
    
    auto normalize = [range](float f)->int{
        if (f < range * -1) {
            return -1;
        } else if (f > range) {
            return 1;
        } else {
            return 0;
        }
    };
    
    Vec2 unitV = Vec2(normalize(v.x), normalize(v.y));
    if (unitV != Vec2::ZERO && unitV != _direction) {
        _direction = unitV;
        runAnimate(unitV);
    }
}