#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include"Object.h"
#include "cocos2d.h"
using namespace cocos2d;
#include<vector>
using namespace std;

class HelloWorld : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    // implement the "static node()" method manually
	void menuCallbackStart(CCObject* pSender);

	void iniparameter();

    CREATE_FUNC(HelloWorld);
};

class Start : public cocos2d::CCLayer
{
public:
	virtual bool init();

	static cocos2d::CCScene* scene();

	void menuCallbackBack(CCObject* pSender);

	void menuCallbackPause(CCObject* pSender);

	CREATE_FUNC(Start);

	void movingBackground(float ft);

	void movingLand(float ft);

	bool judgeCrash(vector<Object*>::iterator i);

	void release();

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);

	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

	virtual void onEnter();

	virtual void onExit();

	void update(float ft);

};

#endif // __HELLOWORLD_SCENE_H__
