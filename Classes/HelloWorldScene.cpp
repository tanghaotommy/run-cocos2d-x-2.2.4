#include "HelloWorldScene.h"
#include"Hero.h"
#include<vector>
using namespace std;

USING_NS_CC;

CCSprite* background1;
CCSprite* background2;
CCSprite* land1;
CCSprite* land2;
float background1x;
float background2x;
float land1x;
float land2x;
float iniHeight;
float landMovespeed;
float backgroundMovespeed;
float screenWidth;
float screenHeight;
float xRatio;
float yRatio;
float jumpHeight = 50*yRatio;
static float Heroscale=0.5;
static float Objectscale=0.5;
static float backgroundSleep=2;
static float landSleep=0.25;
bool continuousAction;
int countEnemy=500;
int currentScore;
CCLabelTTF* score;
Hero* hero;
vector<Object*> object;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	screenWidth = CCDirector::sharedDirector()->getWinSize().width;
	screenHeight = CCDirector::sharedDirector()->getWinSize().height;
	xRatio = screenWidth/480.0;
	yRatio = screenHeight/320.0;
	jumpHeight = 50*yRatio;
	//////////////////////////////
	// 1. super init first
	if ( !CCLayer::init() )
	{
		return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
	CCSprite* bg = CCSprite::create("MainMenu.png");
    bg->setScale(0.5);
    bg->setPosition( ccp(visibleSize.width/2,visibleSize.height/2) );
	this->addChild(bg,0);

    CCMenuItemImage *pCloseItem = CCMenuItemImage::create( "CloseNormal.png", "CloseSelected.png",this,menu_selector(HelloWorld::menuCloseCallback));
    pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 , origin.y + pCloseItem->getContentSize().height/2));
	CCMenuItemImage *newGameItem = CCMenuItemImage::create("newGameA.png", "newGameB.png",this,menu_selector(HelloWorld::menuCallbackStart));
    newGameItem->setScale(0.5);
    newGameItem->setPosition(ccp(visibleSize.width / 2 ,visibleSize.height / 2 ));

	CCMenu *menu = CCMenu::create(pCloseItem,newGameItem,NULL);
	menu->setPosition(0,0);
	this->addChild(menu,1);
    return true;
}

void HelloWorld::menuCallbackStart(CCObject* pSender)
{
		CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInT::create(1.0f,Start::scene()));
}


void HelloWorld::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}

void HelloWorld::iniparameter()
{

}

bool Start::init()
{
	currentScore=0;
	countEnemy=0;
	continuousAction=false;
	setTouchEnabled(true);
	score = CCLabelTTF::create("Hello","arial",20);
	addChild(score,1);

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	CCMenuItemImage *PauseItem = CCMenuItemImage::create("backA.png", "backB.png",this,menu_selector(Start::menuCallbackPause));
	PauseItem->setScale(0.5);
	PauseItem->setPosition(PauseItem->getContentSize().width,visibleSize.height-PauseItem->getContentSize().height);

	CCMenuItemFont *item1 =	CCMenuItemFont::create("BACK",this,menu_selector(Start::menuCallbackBack));
	item1->setPosition(visibleSize.width-item1->getContentSize().width,visibleSize.height-item1->getContentSize().height);
	CCMenu *menu = CCMenu::create(PauseItem,item1,NULL);
	menu->setPosition(0,0);
	this->addChild(menu,1);
	//±í²ã
    land2 = CCSprite::create("road_6.png");	
	land1 = CCSprite::create("road_6.png");
	iniHeight=land1->getContentSize().height/2;	
	land1x=0;
	landMovespeed = land1->getContentSize().width/10.0;

	land2->setAnchorPoint(ccp(0,0));	
	land2x=land1x+land1->getContentSize().width;
	land2->setPosition(ccp(land2x,0));
	this->addChild(land2,-1);
	land2->runAction(CCMoveBy::create(landSleep,ccp(-landMovespeed,0)));
	
	land1->setAnchorPoint(ccp(0,0));	
	land1->setPosition(ccp(land1x,0));
	this->addChild(land1,-1);
	land1->runAction(CCMoveBy::create(landSleep,ccp(-landMovespeed,0)));
	//±³¾°
	background1 = CCSprite::create("background1.png");
	backgroundMovespeed = background1->getContentSize().width/10.0;
	background1->setAnchorPoint(ccp(0,0));
	background1x=0;	
	background1->setPosition(ccp(background1x,0));
	this->addChild(background1,-2);
	background1->runAction(CCMoveBy::create(backgroundSleep,ccp(-backgroundMovespeed,0)));
	
	background2 = CCSprite::create("background2.png");
	background2->setAnchorPoint(ccp(0,0));
	background2x=background1x+background1->getContentSize().width;
	background2->setPosition(ccp(background2x,0));
	this->addChild(background2,-2);
	background2->runAction(CCMoveBy::create(backgroundSleep,ccp(-backgroundMovespeed,0)));

	hero = new Hero(jumpHeight,iniHeight,xRatio,yRatio,Heroscale);
    hero->setScale(Heroscale);
	hero->setPosition(ccp(0,iniHeight));
    addChild(hero,1);

	scheduleUpdate();
	schedule(schedule_selector(Start::movingBackground),backgroundSleep);
	schedule(schedule_selector(Start::movingLand),landSleep);
	return true;
}

void Start::update(float ft)
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	bool judge=false;
	currentScore+=1;
	char temp[10];
	char _score[20]="score:";

	removeChild(score);

	sprintf(temp, "%d", currentScore); 
	strcat(_score,temp);
	score = CCLabelTTF::create(_score,"arial",20);  
	score->setColor(ccc3(0,0,0));
	score->setPosition(ccp(visibleSize.width/2,visibleSize.height-score->getContentSize().height));
	addChild(score,1);

	if(countEnemy>=300)
	{		
		countEnemy=0;
		object.push_back(new Object(xRatio,yRatio,Objectscale));
		(*(object.end()-1))->setScale(Objectscale);
		(*(object.end()-1))->setPosition(visibleSize.width,iniHeight);
		addChild((*(object.end()-1)),0);
	}
	for(vector<Object*>::iterator i=object.begin();i!=object.end();i++)
	{
		if(judgeCrash(i)==true)
		{
			judge=true;
		}
		(*i)->move();
		if((*i)->getPositionX()+(*i)->getContentSize().width<0)
		{
			if(i!=object.end()-1)
			{
				i=object.erase(i);
			}
		}
	}
	if(judge==true)
	{
	    Start::release();
	    background1x=0;
	    background2x=background1->getContentSize().width;
		CCDirector::sharedDirector()->replaceScene(HelloWorld::scene());
	}
	countEnemy++;
}

bool Start::judgeCrash(vector<Object*>::iterator i)
{
	float x1=hero->getPositionX()+30*xRatio*Heroscale,y1=hero->getPositionY()+50*yRatio*Heroscale;
	float x2=hero->getPositionX()+200*xRatio*Heroscale-30*xRatio*Heroscale,y2=y1;
	float left=(*i)->getPositionX()+40*xRatio*(*i)->getscale(),right=(*i)->getPositionX()+126*xRatio*Objectscale-40*xRatio*(*i)->getscale();
	float bottom=(*i)->getPositionY()+30*yRatio*(*i)->getscale(),top=(*i)->getPositionY()+149*yRatio*Objectscale-20*yRatio*(*i)->getscale();
	if((x1>=left && x1<=right && y1>=bottom && y1<=top) || (x2>=left && x2<=right && y2>=bottom && y2<=top))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Start::release()
{
	if(!object.empty())
	{
		object.clear();
	}
}

CCScene *Start::scene()
{
	CCScene *scene = CCScene::create();
	Start *layer = Start::create();
	scene->addChild(layer);
	return scene;
}

void Start::menuCallbackBack(CCObject* pSender)
{
	Start::release();
	background1x=0;
	background2x=background1->getContentSize().width;
	CCDirector::sharedDirector()->replaceScene(HelloWorld::scene());
}

void Start::menuCallbackPause(CCObject* pSender)
{
	if(!CCDirector::sharedDirector()->isPaused())
	{
		CCDirector::sharedDirector()->pause();
	}
	else
	{	
		CCDirector::sharedDirector()->resume();
	}
}

void Start::movingLand(float ft)
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();	
	land1->runAction(CCMoveBy::create(landSleep,ccp(-landMovespeed,0)));
	land2->runAction(CCMoveBy::create(landSleep,ccp(-landMovespeed,0)));
	land2x-=landMovespeed;
	land1x-=landMovespeed;
	if(land1x<=-land1->getContentSize().width)
	{
		land1x=land2x+land1->getContentSize().width;
		land1->setPosition(ccp(land1x,0));
	}
	else
	{
		land1->setPosition(ccp(land1x,0));
	}
	if(land2x<=-land1->getContentSize().width)
	{
		land2x=land1x+land1->getContentSize().width;
		land2->setPosition(ccp(land2x,0));
	}
	else
	{
		land2->setPosition(ccp(land2x,0));
	}
}

void Start::movingBackground(float ft)
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	background1->runAction(CCMoveBy::create(backgroundSleep,ccp(-backgroundMovespeed,0)));
	background1x-=backgroundMovespeed;		
	background2->runAction(CCMoveBy::create(backgroundSleep,ccp(-backgroundMovespeed,0)));
	background2x-=backgroundMovespeed;
	if(background1x<=-background1->getContentSize().width)
	{
		background1x=background2x+background1->getContentSize().width;
		background1->setPosition(ccp(background1x,0));
	}
	else
	{
		background1->setPosition(ccp(background1x,0));
	}

	if(background2x<=-background1->getContentSize().width)
	{
		background2x=background1x+background1->getContentSize().width;
		background2->setPosition(ccp(background2x,0));
	}
	else
	{
		background2->setPosition(ccp(background2x,0));
	}
}

bool Start::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    return true;
}

void Start::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint beginPoint=pTouch->getLocationInView();
    beginPoint=CCDirector::sharedDirector()->convertToGL(beginPoint);
	if(hero->getPositionY()>iniHeight && hero->getPositionY()<2*jumpHeight+iniHeight && continuousAction==true)
	{
		hero->setState(2);
		continuousAction=false;
	}
	if(hero->getPositionY()==iniHeight){
	    hero->setState(1);
		continuousAction=true;
	}
}

void Start::onEnter()
{  
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,0,false);  
	CCLayer::onEnter();  
}  

void Start::onExit()
{  
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);  
	CCLayer::onExit();  
}






