#ifndef __LSFGame_SCENE_H__
#define __LSFGame_SCENE_H__

#include "cocos2d.h"

using namespace cocos2d;

class LSFGame : public cocos2d::LayerColor
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(LSFGame);
	Size winSize;
	Sprite* inventory;
	Sprite* craftUsel;
	Sprite* craftSel;
	Sprite* craft;
	LayerColor* invenLayer;
	MenuItemImage* btn_inventory;
	Menu* inventoryMenu;
	
	
	int btnCount;
	int cbtnCount;
	bool craftSwitch;
	bool modeSwitch;
	virtual void onEnter();
	virtual void onExit();
	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

	//Inventory Scene transition
	void doPushSceneTran(Ref * pSender);
	cocos2d::TransitionScene* createTransition(int nIndex, float t, cocos2d::Scene* s);
};

#endif // __LSFGame_SCENE_H__
