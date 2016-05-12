#ifndef __LSFSINGLETON_H__
#define __LSFSINGLETON_H__

#include "cocos2d.h"
#include "AnimateCreate.h"
using namespace cocos2d;

class LSFSingleton{
private:
	LSFSingleton();
	static LSFSingleton * instance;

	//---------------------------- MainScene Begin
	Sprite* mBack;				
	Sprite* mLogo;
	Animation* mainAnim;		
	Animate* mainAnimate;		
	RepeatForever* mainRep;		

	Animation* logoAnim;		
	Animate* logoAnimate;		
	DelayTime* logoDelay;		
	Sequence* logoSeq;			
	RepeatForever* logoSeqRep;	

	AnimateCreate* animCreate;
	MenuItemImage* mBtn_Start;
	//---------------------------- MainScene End
	//////////////////////////////////////////////
	//---------------------------- GameScene Begin
	
	//---------------------------- GameScene End


public:
	static LSFSingleton * getInstance();
	static void releaseInstance();
	
	//////////////////////////////////////////////////
	// ½Ì±ÛÅæ º¯¼ö Get
	int value;
	Size winSize = Director::getInstance()->getWinSize();
	
	//---------------------------- MainScene Begin
	Sprite* GetmBack();			
	Sprite* GetmLogo();			   
	Animation* GetmainAnim();		
	Animate* GetmainAnimate();		
	RepeatForever* GetmainRep();	
	Animation* GetlogoAnim();		
	Animate* GetlogoAnimate();		
	DelayTime* GetlogoDelay();		
	Sequence* GetlogoSeq();			
	RepeatForever* GetlogoSeqRep();	

	AnimateCreate* GetmAnimCreate();
	MenuItemImage* GetmBtn_Start();
	//---------------------------- MainScene End
	///////////////////////////////////////////////
	//---------------------------- GameScene Begin
	Sprite* GetgBack();
	Sprite* GetgCraft();
	Sprite* GetgRainDrop();
	Sprite* GetgSnowDrop();
	RepeatForever* GetgameRep();
	RepeatForever* GetrainRep();
	RepeatForever* GetsnowRep();
	RepeatForever* GetcraftRep();
	RepeatForever* GetfstNormalRep();
	Repeat* GetfstHangRep();
	Repeat* GetfstSuccessRep();
	Repeat* GetfstFailRep();
	//---------------------------- GameScene End


};
#endif // define __LSFSINGLETON_H__