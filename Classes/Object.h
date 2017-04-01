#ifndef OBJECT_H
#define ONJECT_H
#include"cocos2d.h"
using namespace cocos2d;

class Object : public CCNode
{
private:
	CCSprite* mainsprite;
	float iniHeight;
	float xRatio,yRatio,scale;
public:
	Object(float _xRatio , float _yRatio, float _scale);

	~Object();

	void move();
		
	float getwidth();

	float getheight();

	float getscale();

    virtual void onEnter();

	virtual void onExit();
};

#endif