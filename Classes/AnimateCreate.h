#ifndef __Animate_CREATE__
#define __Animate_CREATE__

#include "cocos2d.h"
#include "..\cocos2d\external\json\rapidjson.h"
#include "..\cocos2d\external\json\document.h"
#include "..\cocos2d\external\json\stringbuffer.h"
#include "..\cocos2d\external\json\writer.h"


using namespace cocos2d;



class AnimateCreate 
{
public:

	virtual bool init();
	
	Animation* CreateAnim(const std::string & json, const std::string & framename, int frames, float dt);
};

#endif // __Animate_CREATE__

