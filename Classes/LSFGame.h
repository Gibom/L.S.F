#ifndef __LSFGame_SCENE_H__
#define __LSFGame_SCENE_H__

#include "cocos2d.h"
#include "Box2D\Box2D.h"
#include <GLES-Render.h>
#include "vrope-x\vrope.h"

using namespace cocos2d;

class LSFGame : public cocos2d::LayerColor
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(LSFGame);

	Size winSize;
	Sprite* ship;
	Sprite* fhisherman;
	Sprite* inventory;
	Sprite* craftUsel;
	Sprite* craftSel;
	Sprite* craft;
	Sprite* rainDrop;
	Sprite* snowDrop;
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
