#include "LSFSingleton.h"

using namespace cocos2d;

LSFSingleton::LSFSingleton() {
	//------------------------------------------------------------------------------------ MainScene Begin
	auto MainFrameCache = SpriteFrameCache::getInstance();
	MainFrameCache->addSpriteFramesWithJson("Sprites/Main.json");
	mBack = Sprite::createWithSpriteFrame(MainFrameCache->getSpriteFrameByName("Main 0.png"));

	MainFrameCache = SpriteFrameCache::getInstance();
	MainFrameCache->addSpriteFramesWithJson("Sprites/Logo.json");
	mLogo = Sprite::createWithSpriteFrame(MainFrameCache->getSpriteFrameByName("Logo 0.png"));

	mainAnim = mAnimCreate->CreateAnim("Sprites/Main.json", "Main", 20, 0.1f);
	mainAnimate = Animate::create(mainAnim);
	mainRep = RepeatForever::create(mainAnimate);

	logoAnim = mAnimCreate->CreateAnim("Sprites/Logo.json", "Logo", 20, 0.1f);
	logoAnimate = Animate::create(logoAnim);
	logoDelay = DelayTime::create(5.f);
	logoSeq = Sequence::create(logoAnimate, logoDelay, nullptr);
	logoSeqRep = RepeatForever::create(logoSeq);
	//------------------------------------------------------------------------------------ MainScene End
	////////////////////////////////////////////////////////////////////////////////////////////////////
	//------------------------------------------------------------------------------------ GameScene Begin

	//------------------------------------------------------------------------------------ GameScene End
}

LSFSingleton * LSFSingleton::instance = NULL;

LSFSingleton * LSFSingleton::getInstance()
{
	if (!instance)
	{
		instance = new LSFSingleton();
	}

	return instance;
}

//변수 접근 함수정의
//--------------------------------------------------------------------- MainScene Begin
Sprite* LSFSingleton::GetmBack() { return mBack; }
Sprite* LSFSingleton::GetmLogo() { return mLogo; }
Animation* LSFSingleton::GetmainAnim() { return mainAnim; }
Animate* LSFSingleton::GetmainAnimate() { return mainAnimate; }
RepeatForever* LSFSingleton::GetmainRep() { return mainRep; }

Animation* LSFSingleton::GetlogoAnim() { return logoAnim; }
Animate* LSFSingleton::GetlogoAnimate() { return logoAnimate; }
DelayTime* LSFSingleton::GetlogoDelay() { return logoDelay; }
Sequence* LSFSingleton::GetlogoSeq() { return logoSeq; }
RepeatForever* LSFSingleton::GetlogoSeqRep() { return logoSeqRep; }

AnimateCreate* LSFSingleton::GetmAnimCreate() { return mAnimCreate; }
MenuItemImage* LSFSingleton::GetmBtn_Start() { return mBtn_Start; }
//--------------------------------------------------------------------- MainScene End
///////////////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------- GameScene Begin

//--------------------------------------------------------------------- GameScene End


void LSFSingleton::releaseInstance()
{
	if (instance) delete instance;
}