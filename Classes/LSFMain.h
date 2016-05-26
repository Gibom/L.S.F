#ifndef __LSFMain_SCENE_H__
#define __LSFMain_SCENE_H__

#include "cocos2d.h"
#include "AnimateCreate.h"
#include "LSFSingleton.h"
#include "SoundEffect.h"

using namespace cocos2d;

class LSFMain : public cocos2d::LayerColor
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    CREATE_FUNC(LSFMain);
	
	SoundEffect* soundEffect;

	MenuItemImage* btn_Start;
	MenuItemImage* btn_Option;
	Menu* mainMenu;
	AnimateCreate* animCreate;
	void doPushSceneTran(Ref * pSender);
	cocos2d::TransitionScene* createTransition(int nIndex, float t, cocos2d::Scene* s);
	Size winSize;
};

#endif // __LSFMain_SCENE_H__

