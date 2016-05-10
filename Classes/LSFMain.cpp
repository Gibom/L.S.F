#include "LSFMain.h"
#include "LSFGame.h"

using namespace cocos2d;
using namespace rapidjson;


Scene* LSFMain::createScene()
{
	auto scene = Scene::create();
	auto layer = LSFMain::create();
	scene->addChild(layer);

	return scene;
}

bool LSFMain::init()
{
	if (!LayerColor::initWithColor(Color4B(0, 0, 0, 255)))
	{
		return false;
	}

	/////////////////////////////
	soundEffect->doSoundAction("main", 0);
	winSize = Director::getInstance()->getWinSize();
	
	//스프라이트 캐시
	Sprite* backDefault = Sprite::create("Sprites/Main_bg.png");
	backDefault->setAnchorPoint(Vec2::ZERO);
	backDefault->setPosition(Vec2::ZERO);
	this->addChild(backDefault);
	
	auto MainFrameCache = SpriteFrameCache::getInstance();
	MainFrameCache->addSpriteFramesWithJson("Sprites/Main.json");

	Sprite* back = Sprite::createWithSpriteFrame(MainFrameCache->getSpriteFrameByName("Main 0.png"));
	back->setAnchorPoint(Vec2(0,1));
	back->setPosition(Vec2(0, winSize.height));
	this->addChild(back);


	MainFrameCache = SpriteFrameCache::getInstance();
	MainFrameCache->addSpriteFramesWithJson("Sprites/Logo.json");

	Sprite* logo = Sprite::createWithSpriteFrame(MainFrameCache->getSpriteFrameByName("Logo 0.png"));
	logo->setAnchorPoint(Vec2(0.5, 0.5));
	logo->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
	this->addChild(logo);

	//메뉴
	btn_Start = MenuItemImage::create("Sprites/Button_start_up.png",
		"Sprites/Button_start_down.png",
		CC_CALLBACK_1(LSFMain::doPushSceneTran, this));

	auto startMenu = Menu::create(btn_Start, nullptr);
	startMenu->setAnchorPoint(Vec2(0.5, 0.5));
	startMenu->setPosition(Vec2(winSize.width / 2, winSize.height / 4));
	startMenu->alignItemsHorizontally();

	this->addChild(startMenu);

	//애니메이션 

	//Background
	auto mainAnim = animCreate->CreateAnim("Sprites/Main.json", "Main", 20, 0.1f);
	auto mainAnimate = Animate::create(mainAnim);
	auto repMain = RepeatForever::create(mainAnimate);
	back->runAction(repMain);

	//Logo
	auto logoAnim = animCreate->CreateAnim("Sprites/Logo.json", "Logo", 20, 0.1f);
	auto logoAnimate = Animate::create(logoAnim);
	auto delayLogo = DelayTime::create(5.f);
	auto seqLogo = Sequence::create(logoAnimate, delayLogo, nullptr);
	auto seqLogoRep = RepeatForever::create(seqLogo);
	logo->runAction(seqLogoRep);

	return true;
}

void LSFMain::doPushSceneTran(Ref * pSender)
{
	soundEffect->doSoundAction("main", 1);
	auto pScene = LSFGame::createScene();
	Director::getInstance()->replaceScene(createTransition(7, 0.5, pScene));
}

TransitionScene* LSFMain::createTransition(int nIndex, float t, Scene* s)
{
	Director::getInstance()->setDepthTest(false);

	switch (nIndex)
	{
		// 점프하면서 Zoom
	case 0: return TransitionJumpZoom::create(t, s);

		// 시계방향으로 침이 돌면서 장면이 바뀜
	case 1: return TransitionProgressRadialCCW::create(t, s);
		// 시계반대방향으로 침이 돌면서 장면이 바뀜
	case 2: return TransitionProgressRadialCW::create(t, s);
	case 3: return TransitionProgressHorizontal::create(t, s);
	case 4: return TransitionProgressVertical::create(t, s);
	case 5: return TransitionProgressInOut::create(t, s);
	case 6: return TransitionProgressOutIn::create(t, s);

		// 교차
	case 7: return TransitionCrossFade::create(t, s);


		// 페이지넘김형식 : PageTransitionForward
	case 8: return TransitionPageTurn::create(t, s, false);
		// 페이지넘김형식 : PageTransitionBackward
	case 9: return TransitionPageTurn::create(t, s, true);
		// 바둑판무늬 좌측하단부터 우측상단순으로 사라짐
	case 10: return TransitionFadeTR::create(t, s);
		// 바툭판무늬 우측상단부터 좌측하단순으로 사라짐
	case 11: return TransitionFadeBL::create(t, s);
		// 하단에서 상단으로 잘라냄
	case 12: return TransitionFadeUp::create(t, s);
		// 상단에서 하단으로 잘라냄
	case 13: return TransitionFadeDown::create(t, s);



		// 바둑판무늬 뿌리기
	case 14: return TransitionTurnOffTiles::create(t, s);


		// 가로로 세등분 나눔
	case 15: return TransitionSplitRows::create(t, s);
		// 세로로 세등분 나눔, 양끝의 두둥분은 밑으로 나머지는 위로
	case 16: return TransitionSplitCols::create(t, s);


		// 페이드인아웃 : 검정 화면
	case 17: return TransitionFade::create(t, s);
		// 페이드인아웃 : 하얀 화면
	case 18: return TransitionFade::create(t, s, Color3B::WHITE);


		// X축(횡선)을 기준으로 회전 : FlipXLeftOver
	case 19: return TransitionFlipX::create(t, s, TransitionScene::Orientation::LEFT_OVER);
		// X축(횡선)을 기준으로 회전 : FlipXRightOver
	case 20: return TransitionFlipX::create(t, s, TransitionScene::Orientation::RIGHT_OVER);
		// Y축(종선)을 기준으로 회전 : FlipYUpOver
	case 21: return TransitionFlipY::create(t, s, TransitionScene::Orientation::UP_OVER);
		// Y축(종선)을 기준으로 회전 : FlipYDownOver
	case 22: return TransitionFlipY::create(t, s, TransitionScene::Orientation::DOWN_OVER);
		// 뒤집어지면서 다음장면으로 넘어감 : FlipAngularLeftOver
	case 23: return TransitionFlipAngular::create(t, s, TransitionScene::Orientation::LEFT_OVER);
		// 뒤집어지면서 다음장면으로 넘어감 : FlipAngularRightOver
	case 24: return TransitionFlipAngular::create(t, s, TransitionScene::Orientation::RIGHT_OVER);


		// X축(횡선)을 기준으로 회전 (확대) : ZoomFlipXLeftOver
	case 25: return TransitionZoomFlipX::create(t, s, TransitionScene::Orientation::LEFT_OVER);
		// X축(횡선)을 기준으로 회전 (확대) : ZoomFlipXRightOver
	case 26: return TransitionZoomFlipX::create(t, s, TransitionScene::Orientation::RIGHT_OVER);
		// Y축(종선)을 기준으로 회전 (확대) : ZoomFlipYUpOver
	case 27: return TransitionZoomFlipY::create(t, s, TransitionScene::Orientation::UP_OVER);
		// Y축(종선)을 기준으로 회전 (확대) : ZoomFlipYDownOver
	case 28: return TransitionZoomFlipY::create(t, s, TransitionScene::Orientation::DOWN_OVER);
		// 뒤집어지면서 다음장면으로 넘어감 (확대) : ZoomFlipAngularLeftOver
	case 29: return TransitionZoomFlipAngular::create(t, s, TransitionScene::Orientation::LEFT_OVER);
		// 뒤집어지면서 다음장면으로 넘어감 (확대) : ZoomFlipAngularRightOver
	case 30: return TransitionZoomFlipAngular::create(t, s, TransitionScene::Orientation::RIGHT_OVER);


		// 이전장면 수축 다음장면 확대
	case 31: return TransitionShrinkGrow::create(t, s);
		// 회전하면서 Zoom
	case 32: return TransitionRotoZoom::create(t, s);


		// 왼쪽에서 다음장면이 나타나서 이전장면을 덮어씀
	case 33: return TransitionMoveInL::create(t, s);
		// 오른쪽에서 다음장면이 나타남
	case 34: return TransitionMoveInR::create(t, s);
		// 위쪽에서 다음장면이 나타남
	case 35: return TransitionMoveInT::create(t, s);
		// 아래쪽에서 다음장면이 나타남
	case 36: return TransitionMoveInB::create(t, s);


		// 왼쪽에서 다음장면이 나타나서 이전장면을 밀어냄
	case 37: return TransitionSlideInL::create(t, s);
		// 오른쪽에서 다음장면이 나타나서 이전장면을 밀어냄
	case 38: return TransitionSlideInR::create(t, s);
		// 위쪽에서 다음장면이 나타나서 이전장면을 밀어냄
	case 39: return TransitionSlideInT::create(t, s);
		// 아래쪽에서 다음장면이 나타나서 이전장면을 밀어냄
	case 40: return TransitionSlideInB::create(t, s);

	default: break;
	}

	return NULL;
}