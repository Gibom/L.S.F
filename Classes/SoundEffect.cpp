#include "SoundEffect.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

//android effect only support ogg
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#define EFFECT_START	"Sounds/Start.ogg"
#define EFFECT_SPLASH	"Sounds/Splash.ogg"
#define EFFECT_WAIT		"Sounds/Wait.ogg"
#define EFFECT_CAST		"Sounds/Cast.ogg"
#define EFFECT_OPEN		"Sounds/Menu_Open.ogg"
#define EFFECT_CLOSE	"Sounds/Menu_Close.ogg"
#define EFFECT_CRAFT	"Sounds/Craft.ogg"
#define EFFECT_TAB		"Sounds/Tab.ogg"
#define EFFECT_MODE			"Sounds/Mode.ogg"
#define EFFECT_HANG			"Sounds/Hang.ogg"
#define EFFECT_FAIL			"Sounds/Fail.ogg"
#define EFFECT_SUCCESS		"Sounds/Success.ogg"
#define EFFECT_GRAB			"Sounds/Grab.ogg"
#define EFFECT_CONSUME		"Sounds/Consume.ogg"
#define EFFECT_REEL			"Sounds/Reel.ogg"
#define EFFECT_COMBINE		"Sounds/Combine.ogg"
#define MUSIC_MAIN		"Sounds/bg_Main.ogg"
#define MUSIC_GAME		"Sounds/bg_Rain.ogg"
#define MUSIC_GAME1		"Sounds/bg_Day.ogg"
#define MUSIC_GAME2		"Sounds/bg_Night.ogg"
#endif // CC_PLATFORM_ANDROID

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#define EFFECT_START		"Sounds/Start.wav"
#define EFFECT_SPLASH		"Sounds/Splash.wav"
#define EFFECT_WAIT			"Sounds/Wait.wav"
#define EFFECT_CAST			"Sounds/Cast.wav"
#define EFFECT_OPEN			"Sounds/Menu_Open.wav"
#define EFFECT_CLOSE		"Sounds/Menu_Close.wav"
#define EFFECT_CRAFT		"Sounds/Craft.wav"
#define EFFECT_TAB			"Sounds/Tab.wav"
#define EFFECT_MODE			"Sounds/Mode.wav"
#define EFFECT_HANG			"Sounds/Hang.wav"
#define EFFECT_FAIL			"Sounds/Fail.wav"
#define EFFECT_SUCCESS		"Sounds/Success.wav"
#define EFFECT_GRAB			"Sounds/Grab.wav"
#define EFFECT_CONSUME		"Sounds/Consume.wav"
#define EFFECT_REEL			"Sounds/Reel.wav"
#define EFFECT_COMBINE		"Sounds/Combine.wav"
#define MUSIC_MAIN			"Sounds/bg_Main.wav"
#define MUSIC_GAME			"Sounds/bg_Rain.wav"
#define MUSIC_GAME1			"Sounds/bg_Day.wav"
#define MUSIC_GAME2			"Sounds/bg_Night.wav"
#endif // CC_PLATFORM_WIN32

bool SoundEffect::init()
{
	log("SoundEffect init");
	//preload background music and effect

	SimpleAudioEngine::getInstance()->preloadBackgroundMusic(MUSIC_MAIN);
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic(MUSIC_GAME);
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic(MUSIC_GAME1);
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic(MUSIC_GAME2);
	SimpleAudioEngine::getInstance()->preloadEffect(EFFECT_SPLASH);
	SimpleAudioEngine::getInstance()->preloadEffect(EFFECT_WAIT);
	SimpleAudioEngine::getInstance()->preloadEffect(EFFECT_CAST);
	SimpleAudioEngine::getInstance()->preloadEffect(EFFECT_OPEN);
	SimpleAudioEngine::getInstance()->preloadEffect(EFFECT_CLOSE);
	SimpleAudioEngine::getInstance()->preloadEffect(EFFECT_CRAFT);
	SimpleAudioEngine::getInstance()->preloadEffect(EFFECT_TAB);
	SimpleAudioEngine::getInstance()->preloadEffect(EFFECT_MODE);
	SimpleAudioEngine::getInstance()->preloadEffect(EFFECT_HANG);
	SimpleAudioEngine::getInstance()->preloadEffect(EFFECT_FAIL);
	SimpleAudioEngine::getInstance()->preloadEffect(EFFECT_SUCCESS);
	SimpleAudioEngine::getInstance()->preloadEffect(EFFECT_GRAB);
	SimpleAudioEngine::getInstance()->preloadEffect(EFFECT_CONSUME);
	SimpleAudioEngine::getInstance()->preloadEffect(EFFECT_REEL);
	SimpleAudioEngine::getInstance()->preloadEffect(EFFECT_START);

	//set default volume
	SimpleAudioEngine::getInstance()->setEffectsVolume(1.0);
	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.1);

	return true;
}

void SoundEffect::onExit()
{
	SimpleAudioEngine::getInstance()->unloadEffect(EFFECT_SPLASH);
	SimpleAudioEngine::getInstance()->unloadEffect(EFFECT_WAIT);
	SimpleAudioEngine::getInstance()->unloadEffect(EFFECT_CAST);
	SimpleAudioEngine::getInstance()->unloadEffect(EFFECT_OPEN);
	SimpleAudioEngine::getInstance()->unloadEffect(EFFECT_CLOSE);
	SimpleAudioEngine::getInstance()->unloadEffect(EFFECT_CRAFT);
	SimpleAudioEngine::getInstance()->unloadEffect(EFFECT_TAB);
	SimpleAudioEngine::getInstance()->unloadEffect(EFFECT_MODE);
	SimpleAudioEngine::getInstance()->unloadEffect(EFFECT_HANG);
	SimpleAudioEngine::getInstance()->unloadEffect(EFFECT_FAIL);
	SimpleAudioEngine::getInstance()->unloadEffect(EFFECT_SUCCESS);
	SimpleAudioEngine::getInstance()->unloadEffect(EFFECT_GRAB);
	SimpleAudioEngine::getInstance()->unloadEffect(EFFECT_CONSUME);
	SimpleAudioEngine::getInstance()->unloadEffect(EFFECT_REEL);
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
	else if (scene == "game") {
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
		case 3:
			SimpleAudioEngine::getInstance()->playEffect(EFFECT_WAIT);
			break;

			//stop All effect
		case 4:
			SimpleAudioEngine::getInstance()->stopAllEffects();
			break;

			//play effect
		case 5:
			SimpleAudioEngine::getInstance()->playEffect(EFFECT_OPEN);
			break;
		case 6:
			SimpleAudioEngine::getInstance()->playEffect(EFFECT_CLOSE);
			break;
		case 7:
			SimpleAudioEngine::getInstance()->playEffect(EFFECT_CRAFT);
			break;
		case 8:
			SimpleAudioEngine::getInstance()->playBackgroundMusic(MUSIC_GAME1, true);
			break;
		case 9:
			SimpleAudioEngine::getInstance()->playBackgroundMusic(MUSIC_GAME2, true);
			break;
		case 10:
			SimpleAudioEngine::getInstance()->playEffect(EFFECT_TAB);
			break;
		case 11:
			SimpleAudioEngine::getInstance()->playEffect(EFFECT_MODE);
			break;
		case 12:
			SimpleAudioEngine::getInstance()->playEffect(EFFECT_HANG);
			break;
		case 13:
			SimpleAudioEngine::getInstance()->playEffect(EFFECT_FAIL);
			break;
		case 14:
			SimpleAudioEngine::getInstance()->playEffect(EFFECT_SUCCESS);
			break;
		case 15:
			SimpleAudioEngine::getInstance()->playEffect(EFFECT_GRAB);
			break;
		case 16:
			SimpleAudioEngine::getInstance()->playEffect(EFFECT_CONSUME);
			break;
		case 17:
			SimpleAudioEngine::getInstance()->playEffect(EFFECT_REEL);
			break;
		case 18:
			SimpleAudioEngine::getInstance()->playEffect(EFFECT_COMBINE);
			break;
		}
	}
}
void SoundEffect::doSoundStop(int effecttype)
{
	if (effecttype == 1) {
		SimpleAudioEngine::getInstance()->stopAllEffects();
	}
	else if (effecttype == 2) {
		SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	}
}
void SoundEffect::test()
{
	log("BGM Volume :%f", SimpleAudioEngine::getInstance()->getBackgroundMusicVolume());
	log("Effect Volume :%f", SimpleAudioEngine::getInstance()->getEffectsVolume());
}
void SoundEffect::doVolumeUpdate(float per, int type)
{
	if (type == 1) {
		SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(per);
	}
	else if (type == 2) {
		SimpleAudioEngine::getInstance()->setEffectsVolume(per);
	}
}