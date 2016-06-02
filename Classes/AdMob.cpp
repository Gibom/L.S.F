#include "AdMob.h"

static AdMob *g_pHello = NULL;
USING_NS_CC;

#if (CC_TARGET_PLATFORM	 == CC_PLATFORM_ANDROID)
#include "platform\android\jni\JniHelper.h"

void callJavaMethod(std::string func)
{
	JniMethodInfo t;
	/*
	JniHelper를 통해 org/cocos2dx/cpp/에 있는
	AppActivity class의 파라미터로 들어온 스트링 이름의 함수 정보를 가져온다.
	*/
	if (JniHelper::getStaticMethodInfo(t
		, "org.cocos2dx.cpp.AppActivity"
		, func.c_str()
		, "()V"))
	{
		//함수 호출
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
		//Release
		t.env->DeleteLocalRef(t.classID);
	}
}
#else
//iOS 개발시 ObjectC에서는 헤더만 추가하면된다.
//#include "Util/Admob/LayerAdmob.h" 
#endif // (CC_TARGET_PLATFORMTFORM == CC_PLATFORM_ANDROID)



Scene* AdMob::createScene()
{
	auto scene = Scene::create();
	auto layer = AdMob::create();
	scene->addChild(layer);

	return scene;
}

bool AdMob::init()
{
	if (!LayerColor::initWithColor(Color4B(255, 255, 255, 0)))
	{
		return false;
	}

	/////////////////////////////

	Size winSize = Director::getInstance()->getWinSize();

	pMenuItem1 = MenuItemImage::create("Sprites/Button_on.png",
											"Sprites/Button_off.png",
			CC_CALLBACK_1(AdMob::doShow, this));
	pMenuItem1->setPositionX(winSize.width / 2 - 400);
	pMenuItem1->setScale(1.2f);

	pMenuItem2 = MenuItemImage::create("Sprites/Button_hon.png",
		"Sprites/Button_hoff.png",
		CC_CALLBACK_1(AdMob::doHide, this));
	pMenuItem2->setPositionX(winSize.width / 2 - 250);
	pMenuItem2->setScale(1.2f);

	pMenuItem3 = MenuItemImage::create("Sprites/Button_fullad.png",
										"Sprites/Button_fullad_down.png",
		CC_CALLBACK_1(AdMob::doFullShow, this));
	pMenuItem3->setPositionX(winSize.width / 2 - 50);
	pMenuItem3->setScale(1.5f);

	pMenu = Menu::create(pMenuItem1, pMenuItem2, pMenuItem3, nullptr);
	
	pMenu->setPosition(Vec2(winSize.width / 2 - 190, winSize.height / 2 - 110));
	this->addChild(pMenu);

	return true;
}

void AdMob::doShow(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	callJavaMethod("ShowAdPopup");
	//	ShowAdmobAds();
#endif
}

void AdMob::doHide(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	callJavaMethod("HideAdPopup");
	//	HideAdmobAds();
#endif

}

void AdMob::doFullShow(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	callJavaMethod("ShowAdFull");
#else
	//	ShowAdmobFullAds();
#endif
}
