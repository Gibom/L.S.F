#ifndef __LFSLOAD_H__
#define __LFSLOAD_H__

#include "cocos2d.h"
#include "AnimateCreate.h"
#include "LSFSingleton.h"

using namespace cocos2d;

class LSFLoad : public LayerColor
{

public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	CREATE_FUNC(LSFLoad);

	Size winSize;
};

#endif //__LFSLOAD_H__
