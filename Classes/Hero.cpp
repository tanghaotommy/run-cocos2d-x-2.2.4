#include"Hero.h"

Hero::Hero(float _jumpHeight,float _iniHeight ,float _xRatio , float _yRatio, float _scale)
{
	jumpHeight = _jumpHeight;
	iniHeight=_iniHeight;
	xRatio = _xRatio;
	yRatio = _yRatio;
	scale = _scale;
}

Hero::~Hero()
{
}
void Hero::onEnter()
{
	CCNode::onEnter();
	mainsprite = CCSprite::create("s_1.png");
	mainsprite->setAnchorPoint(ccp(0,0));
	CCAnimation* animation = CCAnimation::create();
	animation->addSpriteFrameWithFileName("s_1.png");
	animation->addSpriteFrameWithFileName("s_2.png");
	animation->addSpriteFrameWithFileName("s_3.png");
	animation->addSpriteFrameWithFileName("s_4.png");
	animation->addSpriteFrameWithFileName("s_5.png");
	animation->addSpriteFrameWithFileName("s_6.png");
	animation->setDelayPerUnit(0.1f);
	animation->setRestoreOriginalFrame(true);
	mainsprite->runAction(CCRepeatForever::create(CCAnimate::create(animation)));
	addChild(mainsprite);
}

void Hero::onExit()
{
	CCNode::onExit();
}

void Hero::setState(int state)
{
	switch(state){
	case 1://normal jump
		this->stopAllActions();
		mainsprite->stopAllActions();
		this->runAction(CCSequence::create(CCJumpBy::create(0.5,ccp(0,jumpHeight),jumpHeight,1),CCMoveTo::create(0.5,ccp(0,iniHeight)),CCCallFunc::create(this,callfunc_selector(Hero::jumpend)),NULL));
		break;
	case 2://double jump
		this->stopAllActions();
		mainsprite->stopAllActions();
		this->runAction(CCSequence::create(CCJumpBy::create(0.5,ccp(0,jumpHeight),jumpHeight,1),CCMoveTo::create(0.5,ccp(0,iniHeight)),CCCallFunc::create(this,callfunc_selector(Hero::jumpend)),NULL));
		break;
	case 0:
		this->stopAllActions();
		mainsprite->stopAllActions();
		CCAnimation * animation = CCAnimation::create();
		animation->addSpriteFrameWithFileName("s_1.png");
		animation->addSpriteFrameWithFileName("s_2.png");
		animation->addSpriteFrameWithFileName("s_3.png");
		animation->addSpriteFrameWithFileName("s_4.png");
		animation->addSpriteFrameWithFileName("s_5.png");
		animation->addSpriteFrameWithFileName("s_6.png");
		animation->setDelayPerUnit(0.1f);
		animation->setRestoreOriginalFrame(true);
		mainsprite->runAction(CCRepeatForever::create(CCAnimate::create(animation)));
		break;
	}
}

float Hero::getwidth()
{
	return mainsprite->getContentSize().width*xRatio*scale;
}

float Hero::getheight()
{
	return mainsprite->getContentSize().height*yRatio*scale;
}

void Hero::jumpend(){
	Hero::setState(0);
}