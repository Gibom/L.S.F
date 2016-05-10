#ifndef __SOUNDEFFECT_H__
#define __SOUNDEFFECT_H__

#include "cocos2d.h"


class SoundEffect : public cocos2d::LayerColor
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(SoundEffect);

	virtual void onExit();

	unsigned int m_nSoundId;

	void doSoundAction(const std::string & scene, int type);
};

#endif // __SOUNDEFFECT_H__
