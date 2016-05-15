#include "cocos2d.h"
using namespace cocos2d;

class EffectAutoBindingResolver;
class Material_AutoBindings : public cocos2d::LayerColor
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	CREATE_FUNC(Material_AutoBindings);

	Material_AutoBindings();
	virtual ~Material_AutoBindings();
	virtual void onEnter();
	

private:
	EffectAutoBindingResolver *_resolver;
};

