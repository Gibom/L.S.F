#include "LSFBag.h"
#include "LSFGame.h"
using namespace cocos2d;


Scene* LSFBag::createScene()
{
	auto scene = Scene::create();
	auto layer = LSFBag::create();
	scene->addChild(layer);

	return scene;
}

bool LSFBag::init()
{
	if (!LayerColor::initWithColor(Color4B(255, 255, 255, 10)))
	{
		return false;
	}

	//////////////////////////////

	btn_inventory = Sprite::create("Sprites/inventory.png");
	btn_inventory->setAnchorPoint(Vec2::ZERO);
	btn_inventory->setPosition(Vec2(0, 0));
	//btn_inventory->setScale(1f);
	this->addChild(btn_inventory);
	
	

	return true;
}

//void LSFBag::onEnter()
//{
//	Layer::onEnter();
//	//Touch 
//	//싱글 터치 모드로 터치 리스너 등록
//	auto listener = EventListenerTouchOneByOne::create();
//	//Swallow touches only available in OneByOne mode.
//	//핸들링된 터치 이벤트를 터치 이벤트 array에서 지우겠다는 의미다.
//	listener->setSwallowTouches(true);
//
//	listener->onTouchBegan = CC_CALLBACK_2(LSFBag::onTouchBegan, this);
//	listener->onTouchMoved = CC_CALLBACK_2(LSFBag::onTouchMoved, this);
//	listener->onTouchEnded = CC_CALLBACK_2(LSFBag::onTouchEnded, this);
//
//	// The prioriry of the touch listener is based on the draw order of sprite
//	// 터치 리스너의 우선순위를 (노드가) 화면에 그려진 순서대로 한다
//	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
//}
//void LSFBag::onExit()
//{
//
//	_eventDispatcher->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);
//
//	Layer::onExit();
//}
//bool LSFBag::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
//{
//	auto touchPoint = touch->getLocation();
//
//	log("onTOuchBegan id = %d, x = %f, y= %f", touch->getID(), touchPoint.x, touchPoint.y);
//
//	//touch check --------------------------------
//
//	bool bTouch = btn_inventory->getBoundingBox().containsPoint(touchPoint);
//	if (bTouch)
//	{
//		log("Start Clicked");
//		doPushSceneTran(this);
//
//	}
//	return true;
//}
//void LSFBag::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
//{
//	auto touchPoint = touch->getLocation();
//
//	//log("onTouchEnded id = %d, x = %f, y = %f", touch->getID(), touchPoint.x, touchPoint.y);
//}
void LSFBag::doPushSceneTran(Ref * pSender)
{
	auto pScene = LSFGame::createScene();

	Director::getInstance()->popScene();

}
TransitionScene* LSFBag::createTransition(int nIndex, float t, Scene* s)
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