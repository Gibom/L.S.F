#ifndef __LSFMain_SCENE_H__
#define __LSFMain_SCENE_H__

#include "cocos2d.h"
#include "AnimateCreate.h"
#include "LSFSingleton.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"


using namespace cocos2d;

class LSFMain : public cocos2d::LayerColor
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    CREATE_FUNC(LSFMain);
	
	
	LayerColor* OptionLayer;
	MenuItemImage* btn_Start;
	MenuItemImage* btn_Option;
	MenuItemImage* btn_Close;
	Menu* mainMenu;
	Menu* optionMenu;
	Sprite* optionBoard;
	AnimateCreate* animCreate;
	void sliderEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);
	void doPushSceneTran(Ref * pSender);
	cocos2d::TransitionScene* createTransition(int nIndex, float t, cocos2d::Scene* s);
	Size winSize;
	cocos2d::ui::Text* _displayValueLabel;
	cocos2d::ui::Text* _displayValueLabel2;
	
};

#endif // __LSFMain_SCENE_H__

