#include "LSFSingleton.h"

using namespace cocos2d;

LSFSingleton * LSFSingleton::instance = NULL;

LSFSingleton * LSFSingleton::getInstance()
{
	if (!instance)
	{
		instance = new LSFSingleton();
	}

	return instance;
}
//------------------------------------------- MainScene begin
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
//------------------------------------------- MainScene End

void LSFSingleton::releaseInstance()
{
	if (instance) delete instance;
}