#ifndef __Material_AutoBinding__
#define __Material_AutoBinding__

#include "cocos2d.h"
using namespace cocos2d;

class EffectAutoBindingResolver;
class Material_AutoBindings : public cocos2d::LayerColor
{
public:
	virtual bool init();
	Material_AutoBindings();
	virtual ~Material_AutoBindings();

	void mAutoBinding(Sprite* image);
	
	EffectAutoBindingResolver *_resolver;

	
};

#endif
