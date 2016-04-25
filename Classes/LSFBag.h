#ifndef __LSFBag_SCENE_H__
#define __LSFBag_SCENE_H__

#include "cocos2d.h"

using namespace cocos2d;

class LSFBag : public cocos2d::LayerColor
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(LSFBag);

	Sprite* btn_inventory;
	//virtual void onEnter();
	//virtual void onExit();
	//virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	//virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

	//Inventory Scene transition
	void doPushSceneTran(Ref * pSender);
	cocos2d::TransitionScene* createTransition(int nIndex, float t, cocos2d::Scene* s);
};

#endif // __LSFBag_SCENE_H__
