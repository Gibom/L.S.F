#ifndef __LSFSINGLETON_H__
#define __LSFSINGLETON_H__

#include "cocos2d.h"
#include "AnimateCreate.h"
using namespace cocos2d;

class LSFSingleton{
private:
	LSFSingleton() { value = 10; };
	static LSFSingleton * instance;

	//MainScene
	Sprite* mBack;				/*auto MainFrameCache = SpriteFrameCache::getInstance();
								MainFrameCache->addSpriteFramesWithJson("Sprites/Main.json");
								Sprite* back = Sprite::createWithSpriteFrame(MainFrameCache->getSpriteFrameByName("Main 0.png"));*/

	Sprite* mLogo;				/*MainFrameCache = SpriteFrameCache::getInstance();
								MainFrameCache->addSpriteFramesWithJson("Sprites/Logo.json");
								Sprite* logo = Sprite::createWithSpriteFrame(MainFrameCache->getSpriteFrameByName("Logo 0.png"));*/

	Animation* mainAnim;		//= animCreate->CreateAnim("Sprites/Main.json", "Main", 20, 0.1f);
	Animate* mainAnimate;		//= Animate::create(mainAnim);
	RepeatForever* mainRep;		//= RepeatForever::create(mainAnimate);

	Animation* logoAnim;		//= animCreate->CreateAnim("Sprites/Logo.json", "Logo", 20, 0.1f);
	Animate* logoAnimate;		//= Animate::create(logoAnim);
	DelayTime* logoDelay;		//= DelayTime::create(5.f);
	Sequence* logoSeq;			//= Sequence::create(logoAnimate, delayLogo, nullptr);
	RepeatForever* logoSeqRep;	// = RepeatForever::create(seqLogo);

	AnimateCreate* mAnimCreate;
	MenuItemImage* mBtn_Start;

	//GameScene


public:
	static LSFSingleton * getInstance();
	static void releaseInstance();
	
	//////////////////////////////////////////////////
	// ½Ì±ÛÅæ º¯¼ö Get
	int value;
	Size winSize = Director::getInstance()->getWinSize();
	
	//MainScene
	
	Sprite* GetmBack();			  /*auto MainFrameCache = SpriteFrameCache::getInstance();
								MainFrameCache->addSpriteFramesWithJson("Sprites/Main.json");
								Sprite* back = Sprite::createWithSpriteFrame(MainFrameCache->getSpriteFrameByName("Main 0.png"));*/
	
	Sprite* GetmLogo();			   /*MainFrameCache = SpriteFrameCache::getInstance();
								 MainFrameCache->addSpriteFramesWithJson("Sprites/Logo.json");
								 Sprite* logo = Sprite::createWithSpriteFrame(MainFrameCache->getSpriteFrameByName("Logo 0.png"));*/
	
	Animation* GetmainAnim();		//= animCreate->CreateAnim("Sprites/Main.json", "Main", 20, 0.1f);
	Animate* GetmainAnimate();		//= Animate::create(mainAnim);
	RepeatForever* GetmainRep();		//= RepeatForever::create(mainAnimate);

	Animation* GetlogoAnim();		//= animCreate->CreateAnim("Sprites/Logo.json", "Logo", 20, 0.1f);
	Animate* GetlogoAnimate();		//= Animate::create(logoAnim);
	DelayTime* GetlogoDelay();		//= DelayTime::create(5.f);
	Sequence* GetlogoSeq();			//= Sequence::create(logoAnimate, delayLogo, nullptr);
	RepeatForever* GetlogoSeqRep();	// = RepeatForever::create(seqLogo);

	AnimateCreate* GetmAnimCreate();
	MenuItemImage* GetmBtn_Start();

	//GameScene


};
#endif // define __LSFSINGLETON_H__