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
//	//�̱� ��ġ ���� ��ġ ������ ���
//	auto listener = EventListenerTouchOneByOne::create();
//	//Swallow touches only available in OneByOne mode.
//	//�ڵ鸵�� ��ġ �̺�Ʈ�� ��ġ �̺�Ʈ array���� ����ڴٴ� �ǹ̴�.
//	listener->setSwallowTouches(true);
//
//	listener->onTouchBegan = CC_CALLBACK_2(LSFBag::onTouchBegan, this);
//	listener->onTouchMoved = CC_CALLBACK_2(LSFBag::onTouchMoved, this);
//	listener->onTouchEnded = CC_CALLBACK_2(LSFBag::onTouchEnded, this);
//
//	// The prioriry of the touch listener is based on the draw order of sprite
//	// ��ġ �������� �켱������ (��尡) ȭ�鿡 �׷��� ������� �Ѵ�
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
		// �����ϸ鼭 Zoom
	case 0: return TransitionJumpZoom::create(t, s);


		// �ð�������� ħ�� ���鼭 ����� �ٲ�
	case 1: return TransitionProgressRadialCCW::create(t, s);
		// �ð�ݴ�������� ħ�� ���鼭 ����� �ٲ�
	case 2: return TransitionProgressRadialCW::create(t, s);
	case 3: return TransitionProgressHorizontal::create(t, s);
	case 4: return TransitionProgressVertical::create(t, s);
	case 5: return TransitionProgressInOut::create(t, s);
	case 6: return TransitionProgressOutIn::create(t, s);

		// ����
	case 7: return TransitionCrossFade::create(t, s);


		// �������ѱ����� : PageTransitionForward
	case 8: return TransitionPageTurn::create(t, s, false);
		// �������ѱ����� : PageTransitionBackward
	case 9: return TransitionPageTurn::create(t, s, true);
		// �ٵ��ǹ��� �����ϴܺ��� ������ܼ����� �����
	case 10: return TransitionFadeTR::create(t, s);
		// �����ǹ��� ������ܺ��� �����ϴܼ����� �����
	case 11: return TransitionFadeBL::create(t, s);
		// �ϴܿ��� ������� �߶�
	case 12: return TransitionFadeUp::create(t, s);
		// ��ܿ��� �ϴ����� �߶�
	case 13: return TransitionFadeDown::create(t, s);



		// �ٵ��ǹ��� �Ѹ���
	case 14: return TransitionTurnOffTiles::create(t, s);


		// ���η� ����� ����
	case 15: return TransitionSplitRows::create(t, s);
		// ���η� ����� ����, �糡�� �εպ��� ������ �������� ����
	case 16: return TransitionSplitCols::create(t, s);


		// ���̵��ξƿ� : ���� ȭ��
	case 17: return TransitionFade::create(t, s);
		// ���̵��ξƿ� : �Ͼ� ȭ��
	case 18: return TransitionFade::create(t, s, Color3B::WHITE);


		// X��(Ⱦ��)�� �������� ȸ�� : FlipXLeftOver
	case 19: return TransitionFlipX::create(t, s, TransitionScene::Orientation::LEFT_OVER);
		// X��(Ⱦ��)�� �������� ȸ�� : FlipXRightOver
	case 20: return TransitionFlipX::create(t, s, TransitionScene::Orientation::RIGHT_OVER);
		// Y��(����)�� �������� ȸ�� : FlipYUpOver
	case 21: return TransitionFlipY::create(t, s, TransitionScene::Orientation::UP_OVER);
		// Y��(����)�� �������� ȸ�� : FlipYDownOver
	case 22: return TransitionFlipY::create(t, s, TransitionScene::Orientation::DOWN_OVER);
		// ���������鼭 ����������� �Ѿ : FlipAngularLeftOver
	case 23: return TransitionFlipAngular::create(t, s, TransitionScene::Orientation::LEFT_OVER);
		// ���������鼭 ����������� �Ѿ : FlipAngularRightOver
	case 24: return TransitionFlipAngular::create(t, s, TransitionScene::Orientation::RIGHT_OVER);


		// X��(Ⱦ��)�� �������� ȸ�� (Ȯ��) : ZoomFlipXLeftOver
	case 25: return TransitionZoomFlipX::create(t, s, TransitionScene::Orientation::LEFT_OVER);
		// X��(Ⱦ��)�� �������� ȸ�� (Ȯ��) : ZoomFlipXRightOver
	case 26: return TransitionZoomFlipX::create(t, s, TransitionScene::Orientation::RIGHT_OVER);
		// Y��(����)�� �������� ȸ�� (Ȯ��) : ZoomFlipYUpOver
	case 27: return TransitionZoomFlipY::create(t, s, TransitionScene::Orientation::UP_OVER);
		// Y��(����)�� �������� ȸ�� (Ȯ��) : ZoomFlipYDownOver
	case 28: return TransitionZoomFlipY::create(t, s, TransitionScene::Orientation::DOWN_OVER);
		// ���������鼭 ����������� �Ѿ (Ȯ��) : ZoomFlipAngularLeftOver
	case 29: return TransitionZoomFlipAngular::create(t, s, TransitionScene::Orientation::LEFT_OVER);
		// ���������鼭 ����������� �Ѿ (Ȯ��) : ZoomFlipAngularRightOver
	case 30: return TransitionZoomFlipAngular::create(t, s, TransitionScene::Orientation::RIGHT_OVER);


		// ������� ���� ������� Ȯ��
	case 31: return TransitionShrinkGrow::create(t, s);
		// ȸ���ϸ鼭 Zoom
	case 32: return TransitionRotoZoom::create(t, s);


		// ���ʿ��� ��������� ��Ÿ���� ��������� ���
	case 33: return TransitionMoveInL::create(t, s);
		// �����ʿ��� ��������� ��Ÿ��
	case 34: return TransitionMoveInR::create(t, s);
		// ���ʿ��� ��������� ��Ÿ��
	case 35: return TransitionMoveInT::create(t, s);
		// �Ʒ��ʿ��� ��������� ��Ÿ��
	case 36: return TransitionMoveInB::create(t, s);


		// ���ʿ��� ��������� ��Ÿ���� ��������� �о
	case 37: return TransitionSlideInL::create(t, s);
		// �����ʿ��� ��������� ��Ÿ���� ��������� �о
	case 38: return TransitionSlideInR::create(t, s);
		// ���ʿ��� ��������� ��Ÿ���� ��������� �о
	case 39: return TransitionSlideInT::create(t, s);
		// �Ʒ��ʿ��� ��������� ��Ÿ���� ��������� �о
	case 40: return TransitionSlideInB::create(t, s);
	

	default: break;
	}
	return NULL;
}