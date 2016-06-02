#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;

class AdMob : public cocos2d::LayerColor
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(AdMob);

	MenuItemImage* pMenuItem1;
	MenuItemImage* pMenuItem2;
	MenuItemImage* pMenuItem3;
	Menu* pMenu;

	int btnCount = 0;
	void doShow(Ref* pSender);
	void doHide(Ref* pSender);
	void doFullShow(Ref* pSender);
};

#endif // __HELLOWORLD_SCENE_H__
