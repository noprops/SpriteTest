#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

#define North cocos2d::Vec2(0,1)
#define NorthEast cocos2d::Vec2(1,1)
#define East cocos2d::Vec2(1,0)
#define SouthEast cocos2d::Vec2(1,-1)
#define South cocos2d::Vec2(0,-1)
#define SouthWest cocos2d::Vec2(-1,-1)
#define West cocos2d::Vec2(-1,0)
#define NorthWest cocos2d::Vec2(-1,1)

class HelloWorld : public cocos2d::Layer
{
private:
    cocos2d::Sprite* _sprite;
    bool _tint;
    cocos2d::Vec2 _direction;
public:
    HelloWorld();
    virtual ~HelloWorld();
    
    static cocos2d::Scene* createScene();

    virtual bool init() override;
    
    void tintButtonPressed(cocos2d::Ref* sender);
    void setColorButtonPressed(cocos2d::Ref* sender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    
    void runAnimate(const cocos2d::Vec2& direction);
    
    virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) override;
    virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event) override;
    virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event) override;
};

#endif // __HELLOWORLD_SCENE_H__