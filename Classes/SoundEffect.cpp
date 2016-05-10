#include "SoundEffect.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

//android effect only support ogg
//#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#define EFFECT_START	"Sounds/Start.ogg"
#define EFFECT_SPLASH	"Sounds/Splash.ogg"
#define EFFECT_WAIT		"Sounds/Wait.ogg"
#define EFFECT_CAST		"Sounds/Cast.ogg"
#define MUSIC_MAIN		"Sounds/bg_Main.ogg"
#define MUSIC_GAME		"Sounds/bg_Rain.ogg"
//#endif // CC_PLATFORM_ANDROID

//#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
//#define EFFECT_START	"Sounds/Start.wav"
//#define EFFECT_SPLASH		"Sounds/Splash.wav"
//#define EFFECT_WAIT		"Sounds/Wait.wav"
//#define EFFECT_CAST		"Sounds/Cast.wav"
//#define MUSIC_MAIN		"Sounds/bg_Main.wav"
//#define MUSIC_GAME		"Sounds/bg_Rain.wav"
//#endif // CC_PLATFORM_WIN32

bool SoundEffect::init()
{
	log("SoundEffect init");
	//preload background music and effect
	
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic(MUSIC_MAIN);
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic(MUSIC_GAME);
	SimpleAudioEngine::getInstance()->preloadEffect(EFFECT_SPLASH);
	SimpleAudioEngine::getInstance()->preloadEffect(EFFECT_START);

	//set default volume
	SimpleAudioEngine::getInstance()->setEffectsVolume(1.0);
	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.1);

	return true;
}

void SoundEffect::onExit()
{
	SimpleAudioEngine::getInstance()->unloadEffect(EFFECT_SPLASH);
	SimpleAudioEngine::getInstance()->unloadEffect(EFFECT_START);
	SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);

	SimpleAudioEngine::getInstance()->end();

	Layer::onExit();
}

void SoundEffect::doSoundAction(const std::string & scene, int type)
{
	log("doSoundAction Active");
	if (scene == "main") {
		log("main Sound");
		switch (type)
		{
			//play background music
		case 0:
			log("case 0");
			log("%s", MUSIC_MAIN);
			SimpleAudioEngine::getInstance()->playBackgroundMusic(MUSIC_MAIN, true);
			break;
			//play effect
		case 1:
			SimpleAudioEngine::getInstance()->playEffect(EFFECT_START);
			break;
		}
	}
	else if(scene == "game") {
		switch (type)
		{
			//play background music
		case 0:
			SimpleAudioEngine::getInstance()->playBackgroundMusic(MUSIC_GAME, true);
			break;
			//play effect
		case 1:
			SimpleAudioEngine::getInstance()->playEffect(EFFECT_CAST);
			break;
		case 2:
			SimpleAudioEngine::getInstance()->playEffect(EFFECT_SPLASH);
			break;
			//play effect repeatly
		case 3:
			SimpleAudioEngine::getInstance()->playEffect(EFFECT_WAIT, true);
			break;
			//stop effect
		case 4:
			SimpleAudioEngine::getInstance()->stopEffect(m_nSoundId);
			break;

		}
	}
}