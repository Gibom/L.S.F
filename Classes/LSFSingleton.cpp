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

	mainAnim = animCreate->CreateAnim("Sprites/Main.json", "Main", 20, 0.1f);
	mainAnimate = Animate::create(mainAnim);
	mainRep = RepeatForever::create(mainAnimate);

	logoAnim = animCreate->CreateAnim("Sprites/Logo.json", "Logo", 20, 0.1f);
	logoAnimate = Animate::create(logoAnim);
	logoDelay = DelayTime::create(5.f);
	logoSeq = Sequence::create(logoAnimate, logoDelay, nullptr);
	logoSeqRep = RepeatForever::create(logoSeq);
	//------------------------------------------------------------------------------------ MainScene End
	////////////////////////////////////////////////////////////////////////////////////////////////////
	//------------------------------------------------------------------------------------ GameScene Begin
	auto GameFrameCache = SpriteFrameCache::getInstance();
	GameFrameCache->addSpriteFramesWithJson("Sprites/Game_cloudcut.json");
	gBack = Sprite::createWithSpriteFrame(GameFrameCache->getSpriteFrameByName("Game_cloudcut 0.png"));
	
	GameFrameCache = SpriteFrameCache::getInstance();
	GameFrameCache->addSpriteFramesWithJson("Sprites/Button_craft.json");
	gCraft = Sprite::createWithSpriteFrame(GameFrameCache->getSpriteFrameByName("Button_craft 0.png"));

	craftAnim = animCreate->CreateAnim("Sprites/Button_craft.json", "Button_craft", 3, 0.1f);
	craftAnimate = Animate::create(craftAnim);
	craftRep = RepeatForever::create(craftAnimate);

	GameFrameCache = SpriteFrameCache::getInstance();
	GameFrameCache->addSpriteFramesWithJson("Sprites/RainDrop.json");
	gRainDrop = Sprite::createWithSpriteFrame(GameFrameCache->getSpriteFrameByName("RainDrop 0.png"));

	rainAnim = animCreate->CreateAnim("Sprites/RainDrop.json", "RainDrop", 3, 0.1f);
	rainAnimate = Animate::create(rainAnim);
	rainRep = RepeatForever::create(rainAnimate);
	
	GameFrameCache = SpriteFrameCache::getInstance();
	GameFrameCache->addSpriteFramesWithJson("Sprites/SnowDrop.json");
	gSnowDrop = Sprite::createWithSpriteFrame(GameFrameCache->getSpriteFrameByName("SnowDrop 0.png"));

	snowAnim = animCreate->CreateAnim("Sprites/SnowDrop.json", "SnowDrop", 3, 0.1f);
	snowAnimate = Animate::create(snowAnim);
	snowRep = RepeatForever::create(snowAnimate);

	gameAnim = animCreate->CreateAnim("Sprites/Game_cloudcut.json", "Game_cloudcut", 15, 0.1f);
	gameAnimate = Animate::create(gameAnim);
	gameRep = RepeatForever::create(gameAnimate);
	
	fstNormalAnim = animCreate->CreateAnim("Sprites/FishingStat_normal.json", "FishingStat", 4, 0.1f);
	fstNormalAnimate = Animate::create(fstNormalAnim);
	fstNormalRep = RepeatForever::create(fstNormalAnimate);

	fstHangAnim = animCreate->CreateAnim("Sprites/FishingStat_hang.json", "FishingStat", 4, 0.1f);
	fstHangAnimate = Animate::create(fstHangAnim);
	fstHangRep = Repeat::create(fstHangAnimate, 1);

	fstSuccessAnim = animCreate->CreateAnim("Sprites/FishingStat_success.json", "FishingStat", 4, 0.1f);
	fstSuccessAnimate = Animate::create(fstSuccessAnim);
	fstSuccessRep = Repeat::create(fstSuccessAnimate, 1);

	fstFailAnim = animCreate->CreateAnim("Sprites/FishingStat_fail.json", "FishingStat", 4, 0.1f);
	fstFailAnimate = Animate::create(fstFailAnim);
	fstFailRep = Repeat::create(fstFailAnimate, 1);

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

AnimateCreate* LSFSingleton::GetmAnimCreate() { return animCreate; }
MenuItemImage* LSFSingleton::GetmBtn_Start() { return mBtn_Start; }
//--------------------------------------------------------------------- MainScene End
///////////////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------- GameScene Begin
Sprite* LSFSingleton::GetgBack() { return gBack; }
Sprite* LSFSingleton::GetgCraft() { return gCraft; }
Sprite* LSFSingleton::GetgRainDrop() { return gRainDrop; }
Sprite* LSFSingleton::GetgSnowDrop() { return gSnowDrop; }
RepeatForever* LSFSingleton::GetgameRep() { return gameRep; }
RepeatForever* LSFSingleton::GetrainRep() { return rainRep; }
RepeatForever* LSFSingleton::GetsnowRep() { return snowRep; }
RepeatForever* LSFSingleton::GetcraftRep() { return craftRep; }
RepeatForever* LSFSingleton::GetfstNormalRep() { return fstNormalRep; }
Repeat* LSFSingleton::GetfstHangRep() { return fstHangRep; }
Repeat* LSFSingleton::GetfstSuccessRep() { return fstSuccessRep; }
Repeat* LSFSingleton::GetfstFailRep() { return fstFailRep; }
//--------------------------------------------------------------------- GameScene End


void LSFSingleton::releaseInstance()
{
	if (instance) delete instance;
}