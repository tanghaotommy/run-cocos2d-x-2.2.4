#include"Object.h"

Object::Object(float _xRatio , float _yRatio, float _scale)
{
	xRatio=_xRatio;
	yRatio=-yRatio;
	scale=_scale;
}

Object::~Object()
{
}

void Object::onEnter()
{
	CCNode::onEnter();
	mainsprite = CCSprite::create("enemy.png");
	mainsprite->setAnchorPoint(ccp(0,0));
	addChild(mainsprite);
}

void Object::onExit()
{
	CCNode::onExit();
}

void Object::move()
{
	this->runAction(CCMoveBy::create(0.5,ccp(-5,0)));
}

float Object::getwidth()
{
	return mainsprite->getContentSize().width*xRatio*scale;
}

float Object::getheight()
{
	return mainsprite->getContentSize().height*0.5;
}

float Object::getscale()
{
	return scale;
}