#include "LSFGame.h"

using namespace cocos2d;


Scene* LSFGame::createScene()
{
	auto scene = Scene::create();
	auto layer = LSFGame::create();
	scene->addChild(layer);

	return scene;
}

bool LSFGame::init()
{
	if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255)))
	{
		return false;
	}
	
	//////////////////////////////
	
	winSize = Director::getInstance()->getWinSize();
	btnCount = 0;
	cbtnCount = 0;
	craftSwitch = false;
	//��������Ʈ ĳ��
	auto GameFrameCache = SpriteFrameCache::getInstance();
	GameFrameCache->addSpriteFramesWithJson("Sprites/Game.json");

	Sprite* back = Sprite::createWithSpriteFrame(GameFrameCache->getSpriteFrameByName("Game 0.png"));
	back->setAnchorPoint(Vec2::ZERO);
	back->setPosition(Vec2(0, 0));
	back->setScaleY(0.5f);
	this->addChild(back);
	
	auto weatherFrameCache = SpriteFrameCache::getInstance();
	weatherFrameCache->addSpriteFramesWithJson("Sprites/RainDrop.json");

	rainDrop = Sprite::createWithSpriteFrame(weatherFrameCache->getSpriteFrameByName("RainDrop 0.png"));
	rainDrop->setAnchorPoint(Vec2(0.5, 0.5));
	rainDrop->setPosition(Vec2(180, 320));
	this->addChild(rainDrop);

	weatherFrameCache = SpriteFrameCache::getInstance();
	weatherFrameCache->addSpriteFramesWithJson("Sprites/SnowDrop.json");

	snowDrop = Sprite::createWithSpriteFrame(weatherFrameCache->getSpriteFrameByName("SnowDrop 0.png"));
	snowDrop->setAnchorPoint(Vec2(0.5, 0.5));
	snowDrop->setPosition(Vec2(190, 320));
	this->addChild(snowDrop);

	//���� ���̾� �߰�
	//����------------------------------------------------------------------------------------------------
	invenLayer = LayerColor::create(Color4B(255, 255, 255, 125),
		winSize.width, winSize.height);
	invenLayer->setAnchorPoint(Vec2::ZERO);
	invenLayer->setPosition(Vec2(0, 0));
	invenLayer->setVisible(false);
	invenLayer->setScaleY(2.f);
	//invenLayer->setCascadeOpacityEnabled(true);
	back->addChild(invenLayer);

	craftUsel = Sprite::create("Sprites/inventory_bg2.png");
	craftUsel->setAnchorPoint(Vec2(0.5, 0.5));
	craftUsel->setPosition(Vec2(180, 320));
	craftUsel->setCascadeOpacityEnabled(true);
	craftUsel->setOpacity(125);
	invenLayer->addChild(craftUsel);
	
	craftSel = Sprite::create("Sprites/inventory_bg3.png");
	craftSel->setAnchorPoint(Vec2(0.5, 0.5));
	craftSel->setPosition(Vec2(180, 320));
	craftSel->setCascadeOpacityEnabled(true);
	craftSel->setOpacity(125);
	craftSel->setVisible(false);
	invenLayer->addChild(craftSel);


	inventory = Sprite::create("Sprites/inventory_bg.png");
	inventory->setAnchorPoint(Vec2(0.5, 0.5));
	inventory->setPosition(Vec2(184, 320));
	//inventory->setScale(0.5f,1.5f);
	inventory->setCascadeOpacityEnabled(true);
	inventory->setOpacity(255);
	inventory->setVisible(false);
	invenLayer->addChild(inventory);

	GameFrameCache = SpriteFrameCache::getInstance();
	GameFrameCache->addSpriteFramesWithJson("Sprites/Button_craft.json");

	craft = Sprite::createWithSpriteFrame(GameFrameCache->getSpriteFrameByName("Button_craft 0.png"));
	craft->setAnchorPoint(Vec2::ZERO);
	craft->setPosition(Vec2(38, 40));
	craft->setScale(0.8f);
	//craft->setVisible(false);
	invenLayer->addChild(craft);
	//����----------------------------------------------------------------------------------------------------


	//ȯ�� ��������ġ------------------------------------------------------------------------------------------------

	ship = Sprite::create("Sprites/Ship.png");
	ship->setAnchorPoint(Vec2(0.5, 0.5));
	ship->setPosition(Vec2(240, 210));
	ship->setZOrder(2);
	ship->setScale(1.5f);
	this->addChild(ship);

	fhisherman = Sprite::create("Sprites/Fisherman.png");
	fhisherman->setAnchorPoint(Vec2::ZERO);
	fhisherman->setPosition(Vec2(-4, 24));
	fhisherman->setZOrder(1);
	ship->addChild(fhisherman);
	


	//ȯ�� ��������ġ------------------------------------------------------------------------------------------------

	//�޴�
	btn_inventory = MenuItemImage::create("Sprites/Button_bagclose.png",
										  "Sprites/Button_bagopen.png",
										  CC_CALLBACK_1(LSFGame::doPushSceneTran, this));

	inventoryMenu = Menu::create(btn_inventory, nullptr);
	inventoryMenu->setAnchorPoint(Vec2::ZERO);
	inventoryMenu->setPosition(Vec2(290, 70));
	inventoryMenu->setScale(1.f);
	inventoryMenu->alignItemsHorizontally();
	this->addChild(inventoryMenu);

	

	//this->addChild(btn_inventory);
	////�ִϸ��̼� - (�ڵ� ���� �۾� �� addSpriteFramesWithJson �Լ����� for ������ animation �����ϴ� ��� �߰�, animation �������� �Ķ���� bool������ )

	//Background
	auto gameAnimation = Animation::create();
	gameAnimation->setDelayPerUnit(0.5f);
	gameAnimation->addSpriteFrame(GameFrameCache->getSpriteFrameByName("Game 0.png"));
	gameAnimation->addSpriteFrame(GameFrameCache->getSpriteFrameByName("Game 1.png"));
	gameAnimation->addSpriteFrame(GameFrameCache->getSpriteFrameByName("Game 2.png"));
	gameAnimation->addSpriteFrame(GameFrameCache->getSpriteFrameByName("Game 3.png"));
	gameAnimation->addSpriteFrame(GameFrameCache->getSpriteFrameByName("Game 4.png"));
	gameAnimation->addSpriteFrame(GameFrameCache->getSpriteFrameByName("Game 5.png"));
	gameAnimation->addSpriteFrame(GameFrameCache->getSpriteFrameByName("Game 6.png"));
	gameAnimation->addSpriteFrame(GameFrameCache->getSpriteFrameByName("Game 7.png"));
	gameAnimation->addSpriteFrame(GameFrameCache->getSpriteFrameByName("Game 8.png"));
	gameAnimation->addSpriteFrame(GameFrameCache->getSpriteFrameByName("Game 9.png"));
	gameAnimation->addSpriteFrame(GameFrameCache->getSpriteFrameByName("Game 10.png"));
	gameAnimation->addSpriteFrame(GameFrameCache->getSpriteFrameByName("Game 11.png"));
	gameAnimation->addSpriteFrame(GameFrameCache->getSpriteFrameByName("Game 12.png"));
	gameAnimation->addSpriteFrame(GameFrameCache->getSpriteFrameByName("Game 13.png"));
	gameAnimation->addSpriteFrame(GameFrameCache->getSpriteFrameByName("Game 14.png"));
	gameAnimation->addSpriteFrame(GameFrameCache->getSpriteFrameByName("Game 15.png"));
	gameAnimation->retain();
	
	auto craftAnimation = Animation::create();
	craftAnimation->setDelayPerUnit(0.1f);
	craftAnimation->addSpriteFrame(GameFrameCache->getSpriteFrameByName("Button_craft 0.png"));
	craftAnimation->addSpriteFrame(GameFrameCache->getSpriteFrameByName("Button_craft 1.png"));
	craftAnimation->addSpriteFrame(GameFrameCache->getSpriteFrameByName("Button_craft 2.png"));
	craftAnimation->addSpriteFrame(GameFrameCache->getSpriteFrameByName("Button_craft 3.png"));
	craftAnimation->retain();

	auto rainAnimation = Animation::create();
	rainAnimation->setDelayPerUnit(0.1f);
	rainAnimation->addSpriteFrame(weatherFrameCache->getSpriteFrameByName("RainDrop 0.png"));
	rainAnimation->addSpriteFrame(weatherFrameCache->getSpriteFrameByName("RainDrop 1.png"));
	rainAnimation->addSpriteFrame(weatherFrameCache->getSpriteFrameByName("RainDrop 2.png"));
	rainAnimation->addSpriteFrame(weatherFrameCache->getSpriteFrameByName("RainDrop 3.png"));
	rainAnimation->retain();

	auto snowAnimation = Animation::create();
	snowAnimation->setDelayPerUnit(0.1f);
	snowAnimation->addSpriteFrame(weatherFrameCache->getSpriteFrameByName("SnowDrop 0.png"));
	snowAnimation->addSpriteFrame(weatherFrameCache->getSpriteFrameByName("SnowDrop 1.png"));
	snowAnimation->addSpriteFrame(weatherFrameCache->getSpriteFrameByName("SnowDrop 2.png"));
	snowAnimation->addSpriteFrame(weatherFrameCache->getSpriteFrameByName("SnowDrop 3.png"));
	snowAnimation->retain();


	////�ִϸ��̼� ����

	//Background
	auto backAnimate = Animate::create(gameAnimation);
	auto backRep = RepeatForever::create(backAnimate);
	back->runAction(backRep);

	auto craftAnimate = Animate::create(craftAnimation);
	auto craftRep = RepeatForever::create(craftAnimate);
	craft->runAction(craftRep);

	auto rainAnimate = Animate::create(rainAnimation);
	auto rainRep = RepeatForever::create(rainAnimate);
	rainDrop->runAction(rainRep);

	auto snowAnimate = Animate::create(snowAnimation);
	auto snowRep = RepeatForever::create(snowAnimate);
	snowDrop->runAction(snowRep);

	return true;
}

void LSFGame::onEnter()
{
	Layer::onEnter();
	//Touch 
	//�̱� ��ġ ���� ��ġ ������ ���
	auto listener = EventListenerTouchOneByOne::create();
	//Swallow touches only available in OneByOne mode.
	//�ڵ鸵�� ��ġ �̺�Ʈ�� ��ġ �̺�Ʈ array���� ����ڴٴ� �ǹ̴�.
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(LSFGame::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(LSFGame::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(LSFGame::onTouchEnded, this);

	// The prioriry of the touch listener is based on the draw order of sprite
	// ��ġ �������� �켱������ (��尡) ȭ�鿡 �׷��� ������� �Ѵ�
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}
void LSFGame::onExit()
{

	_eventDispatcher->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);

	Layer::onExit();
}
bool LSFGame::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
	auto touchPoint = touch->getLocation();

	log("onTOuchBegan id = %d, x = %f, y= %f", touch->getID(), touchPoint.x, touchPoint.y);

	//touch check --------------------------------

	bool bTouch_craft = craft->getBoundingBox().containsPoint(touchPoint);
	bool bTouch_mode; //��� ����ġ ���� �� ���
	// ������ �����ְ� craft�� ���� ���� ��
	if (bTouch_craft && cbtnCount == 1)
	{
		if (craftSwitch == true)
		{
			craftUsel->setVisible(true);
			craftSel->setVisible(false);
			craftSwitch = false;
			log("craftSwitch Status: Off", craftSwitch);
		}
		else {
			craftUsel->setVisible(false);
			craftSel->setVisible(true);
			craftSwitch = true;
			log("craftSwitch Status: On", craftSwitch);
		}
		
	}
	return true;
}
void LSFGame::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{
	auto touchPoint = touch->getLocation();

	//log("onTouchEnded id = %d, x = %f, y = %f", touch->getID(), touchPoint.x, touchPoint.y);
}
void LSFGame::doPushSceneTran(Ref * pSender)
{
	//auto pScene = LSFGame::createScene();
	//Director::getInstance()->pushScene(createTransition(35, 1, pScene));
	if (btnCount == 0) {
		invenLayer->setVisible(true);
		inventory->setVisible(true);
		//craft->setVisible(true);
		btn_inventory->selected();
		btnCount++;
		cbtnCount = 1;
	}
	else {
		invenLayer->setVisible(false);
		inventory->setVisible(false);
		//craft->setVisible(false);
		btn_inventory->unselected();
		btnCount = 0;
		cbtnCount = 0;
	}
}
TransitionScene* LSFGame::createTransition(int nIndex, float t, Scene* s)
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