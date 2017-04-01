#ifndef HERO_H
#define HERO_H
#include"cocos2d.h"
using namespace cocos2d;

class Hero : public CCNode
{
private:
	CCSprite *mainsprite;
	float iniHeight;
	float jumpHeight;
	float xRatio;
	float yRatio;
	float scale;
public:
	Hero(float _jumpHeight,float _iniHeight ,float _xRatio , float _yRatio,float _scale);

	~Hero();

	float getwidth();

	float getheight();

	virtual void onEnter();

	virtual void onExit();

	void setState(int state);

	void jumpend();
};

#endif