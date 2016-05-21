#ifndef __LSFENV__
#define __LSFENV__

#include "cocos2d.h"

using namespace cocos2d;

class LSFEnv
{
	public:

		virtual bool init();
		void worldDate(float dt);
		void worldWeather(float dt);
		void fishingProb(float dt);
};

#endif // define __LSFENV__