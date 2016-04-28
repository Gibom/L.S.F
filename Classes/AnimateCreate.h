#ifndef __Animate_CREATE__
#define __Animate_CREATE__

#include "cocos2d.h"
#include "D:\LSF_Project\cocos2d\external\json\rapidjson.h"
#include "D:\LSF_Project\cocos2d\external\json\document.h"
#include "D:\LSF_Project\cocos2d\external\json\stringbuffer.h"
#include "D:\LSF_Project\cocos2d\external\json\writer.h"

using namespace cocos2d;



class AnimateCreate : public cocos2d::LayerColor
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(AnimateCreate);


};

#endif // __Animate_CREATE__

