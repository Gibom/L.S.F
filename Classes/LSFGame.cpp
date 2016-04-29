#include "LSFGame.h"

using namespace cocos2d;

int ropeHealth = 10000;
bool fishingStat;
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

	ropes = new std::vector<VRope*>;
	winSize = Director::getInstance()->getWinSize();
	//flow
	texture = Director::getInstance()->getTextureCache()->addImage("Sprites/flow.png");
	//flow
	btnCount = 0;
	cbtnCount = 0;
	waterCount = 0;
	fishingStat = false;
	ropeTickCount = false;
	craftSwitch = false;
	//��������Ʈ ĳ��
	auto GameFrameCache = SpriteFrameCache::getInstance();
	GameFrameCache->addSpriteFramesWithJson("Sprites/Game.json");

	back = Sprite::createWithSpriteFrame(GameFrameCache->getSpriteFrameByName("Game 0.png"));
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
	//invenLayer->setScaleY(2.f);
	//invenLayer->setCascadeOpacityEnabled(true);
	this->addChild(invenLayer, 4);

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


	//ȯ�� ��������ġ-----------------------------------------------------------------------------------------
	weatherCount = 2;
	auto ShipFrameCache = SpriteFrameCache::getInstance();
	if (weatherCount == 1) {
		ShipFrameCache->addSpriteFramesWithJson("Sprites/Ship_normal.json");
	}
	else if (weatherCount == 2) {
		ShipFrameCache->addSpriteFramesWithJson("Sprites/Ship_Windy.json");
	}
	//ShipFrameCache->addSpriteFramesWithJson("Sprites/Ship_normal.json");
	ship = Sprite::createWithSpriteFrame(ShipFrameCache->getSpriteFrameByName("Ship 0.png"));
	ship->setAnchorPoint(Vec2(0.5, 0.5));
	ship->setPosition(Vec2(240, 210));
	ship->setZOrder(2);
	ship->setScale(1.5f);
	this->addChild(ship);

	fisherman = Sprite::create("Sprites/Fisherman.png");
	fisherman->setAnchorPoint(Vec2::ZERO);
	fisherman->setPosition(Vec2(-4, 24));
	fisherman->setZOrder(1);
	ship->addChild(fisherman);



	//ȯ�� ��������ġ----------------------------------------------------------------------------------------

	//�޴�
	btn_inventory = MenuItemImage::create("Sprites/Button_bagclose.png",
		"Sprites/Button_bagopen.png",
		CC_CALLBACK_1(LSFGame::doPushInventory, this));

	inventoryMenu = Menu::create(btn_inventory, nullptr);
	inventoryMenu->setAnchorPoint(Vec2::ZERO);
	inventoryMenu->setPosition(Vec2(290, 70));
	inventoryMenu->setScale(1.f);
	inventoryMenu->alignItemsHorizontally();
	this->addChild(inventoryMenu, 4);



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


	auto shipNormal = Animation::create();
	shipNormal->setDelayPerUnit(0.1f);
	shipNormal->addSpriteFrame(ShipFrameCache->getSpriteFrameByName("Ship 0.png"));
	shipNormal->addSpriteFrame(ShipFrameCache->getSpriteFrameByName("Ship 1.png"));
	shipNormal->addSpriteFrame(ShipFrameCache->getSpriteFrameByName("Ship 2.png"));
	shipNormal->addSpriteFrame(ShipFrameCache->getSpriteFrameByName("Ship 3.png"));
	shipNormal->addSpriteFrame(ShipFrameCache->getSpriteFrameByName("Ship 4.png"));
	shipNormal->addSpriteFrame(ShipFrameCache->getSpriteFrameByName("Ship 5.png"));
	shipNormal->retain();

	auto shipWindy = Animation::create();
	shipWindy->setDelayPerUnit(0.1f);
	shipWindy->addSpriteFrame(ShipFrameCache->getSpriteFrameByName("Ship 0.png"));
	shipWindy->addSpriteFrame(ShipFrameCache->getSpriteFrameByName("Ship 1.png"));
	shipWindy->addSpriteFrame(ShipFrameCache->getSpriteFrameByName("Ship 2.png"));
	shipWindy->addSpriteFrame(ShipFrameCache->getSpriteFrameByName("Ship 3.png"));
	shipWindy->addSpriteFrame(ShipFrameCache->getSpriteFrameByName("Ship 4.png"));
	shipWindy->addSpriteFrame(ShipFrameCache->getSpriteFrameByName("Ship 5.png"));
	shipWindy->retain();


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
	rainRep = RepeatForever::create(rainAnimate);
	rainDrop->runAction(rainRep);

	auto snowAnimate = Animate::create(snowAnimation);
	auto snowRep = RepeatForever::create(snowAnimate);
	snowDrop->runAction(snowRep);


	auto shipAnimate = Animate::create(shipWindy);
	auto shipRep = RepeatForever::create(shipAnimate);
	ship->runAction(shipRep);

	//���� ����
	if (this->createBox2dWorld(true))
	{
		this->schedule(schedule_selector(LSFGame::tick));
		water = WaterNode::create();
		this->addChild(water, 3);
	}

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
	_eventDispatcher->removeAllEventListeners();
	Layer::onExit();
}
bool LSFGame::onTouchBegan(Touch* touch, Event* event)
{
	weatherCount = 1;
	Vec2 touchPoint = touch->getLocation();

	log("onTOuchBegan id = %d, x = %f, y= %f", touch->getID(), touchPoint.x, touchPoint.y);

	//touch check --------------------------------
	bool bTouch_craft = craft->getBoundingBox().containsPoint(touchPoint);
	bool bTouch_mode; //��� ����ġ ���� �� ���

	// ���� ȭ��
	if (cbtnCount == 0) {

		if (fishingStat == false) {
			b2Body* body1 = this->addNewSpriteAt(touchPoint);
			Vec2 fVec = fisherman->convertToWorldSpace(fisherman->getPosition());

			this->createRope(groundBody,
				b2Vec2((fVec.x + 16) / PTM_RATIO, (fVec.y - 4) / PTM_RATIO),
				body1,
				body1->GetLocalCenter(),
				1.1f);

			ropeTouchCount = true;

		}
	}
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
void LSFGame::onTouchMoved(Touch* touch, Event* event)
{

}
void LSFGame::onTouchEnded(Touch* touch, Event* event)
{
	auto touchPoint = touch->getLocation();
	touchRope = touchPoint;
	float test;

	test = touchPoint.y;
	log("%f", test);
	if (cbtnCount != 1 && fishingStat == false) {
		this->scheduleOnce(schedule_selector(LSFGame::ropeTouch), test / 460);
		fishingStat = true;
	}
	//log("onTouchEnded id = %d, x = %f, y = %f", touch->getID(), touchPoint.x, touchPoint.y);
}
void LSFGame::doPushInventory(Ref * pSender)
{
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
bool LSFGame::createBox2dWorld(bool debug)
{
	//���� ���� ����-----------------------------------------------------

	//�߷��� ������ �����Ѵ�.
	b2Vec2 gravity = b2Vec2(0.0f, -5.0f);

	//���带 �����Ѵ�.
	_world = new b2World(gravity);
	_world->SetAllowSleeping(true);
	_world->SetContinuousPhysics(true);

	//����� ����� ����
	if (debug) {
		m_debugDraw = new GLESDebugDraw(PTM_RATIO);
		_world->SetDebugDraw(m_debugDraw);

		uint32 flags = 0;
		flags += b2Draw::e_shapeBit;
		flags += b2Draw::e_jointBit;
		//flags += b2Draw::e_aabbBit;
		//flags += b2Draw::e_pairBit;
		//flags += b2Draw::e_centerOfMassBit;
		m_debugDraw->SetFlags(flags);
	}
	//�޽� ������ �� ���Ե� �ٵ���� ���߰�(sleep)�� ������ �����Ѵ�.
	_world->SetAllowSleeping(true);
	//�������� �����ۿ��� �� ������ �����Ѵ�. : �׽�Ʈ
	_world->SetContinuousPhysics(true);
	////�����ڸ�(�׵θ�)�� ������ ���� (Ground Box)�� �����.
	//�ٵ����� ��ǥ�� �����Ѵ�.
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0, 0);
	//���忡 �ٵ����� ����(��ǥ)�� �ٵ� �����.
	groundBody = _world->CreateBody(&groundBodyDef);

	//�����ڸ�(�׵θ�) ��輱�� �׸� �� �ִ� ����� ��ü�� �����.
	b2EdgeShape groundEdge;
	b2FixtureDef boxShapeDef;
	boxShapeDef.shape = &groundEdge;

	//���� ����� ��ü�� Set( ��1, ��2)�� ���� �����.
	//�׸��� �ٵ�(groundBody)�� ���(groundEdge)�� ������Ų��.

	//�ٴ� �Ʒ�
	groundEdge.Set(b2Vec2(0, 1.4f), b2Vec2(winSize.width / PTM_RATIO, 1.4f));
	groundBody->CreateFixture(&boxShapeDef);
	groundEdge.Set(b2Vec2(0, 1.0f), b2Vec2(winSize.width / PTM_RATIO, 1.0f));
	groundBody->CreateFixture(&boxShapeDef);
	groundEdge.Set(b2Vec2(0, 0.6f), b2Vec2(winSize.width / PTM_RATIO, 0.6f));
	groundBody->CreateFixture(&boxShapeDef);
	groundEdge.Set(b2Vec2(0, 0), b2Vec2(winSize.width / PTM_RATIO, 0));
	groundBody->CreateFixture(&boxShapeDef);

	//����
	groundEdge.Set(b2Vec2(0, 0), b2Vec2(0, winSize.height / PTM_RATIO));
	groundBody->CreateFixture(&boxShapeDef);

	//����
	groundEdge.Set(b2Vec2(0, winSize.height / PTM_RATIO),
		b2Vec2(winSize.width / PTM_RATIO, winSize.height / PTM_RATIO));
	groundBody->CreateFixture(&boxShapeDef);

	//������
	groundEdge.Set(b2Vec2(winSize.width / PTM_RATIO, winSize.height / PTM_RATIO),
		b2Vec2(winSize.width / PTM_RATIO, 0));
	groundBody->CreateFixture(&boxShapeDef);


	//���� ���� �� ---------------------------------------------------


	//Flow
	//bottom
	flowBody0 = this->addNewSpriteFlow(Vec2((winSize.width / 2) + 30, 30), Size(100, 10), b2_dynamicBody, "flowimage", 0);
	flowBody1 = this->addNewSpriteFlow(Vec2(winSize.width / 2, 20), Size(20, 20), b2_dynamicBody, nullptr, 0);
	flowBody2 = this->addNewSpriteFlow(Vec2((winSize.width / 2) + 60, 20), Size(20, 20), b2_dynamicBody, nullptr, 0);

	b2Vec2 axis(0.0f, 1.0f);

	flowJd1.Initialize(flowBody0, flowBody1, flowBody1->GetPosition(), axis);
	flowJd1.motorSpeed = 30.0f;
	flowJd1.maxMotorTorque = 30.0f;
	flowJd1.enableMotor = true;
	flowJd1.frequencyHz = 4.0f;
	flowJd1.dampingRatio = 0.7f;


	flowJd2.Initialize(flowBody0, flowBody2, flowBody2->GetPosition(), axis);
	flowJd2.motorSpeed = 30.0f;
	flowJd2.maxMotorTorque = 30.0f;
	flowJd2.enableMotor = true;
	flowJd2.frequencyHz = 4.0f;
	flowJd2.dampingRatio = 1.0f;

	//center
	flowBody3 = this->addNewSpriteFlow(Vec2((winSize.width / 2) + 30, 80), Size(100, 5), b2_dynamicBody, "flowimage", 0);
	flowBody4 = this->addNewSpriteFlow(Vec2(winSize.width / 2, 70), Size(10, 10), b2_dynamicBody, nullptr, 0);
	flowBody5 = this->addNewSpriteFlow(Vec2((winSize.width / 2) + 60, 70), Size(10, 10), b2_dynamicBody, nullptr, 0);

	flowJd3.Initialize(flowBody3, flowBody4, flowBody4->GetPosition(), axis);
	flowJd3.motorSpeed = 25.0f;
	flowJd3.maxMotorTorque = 25.0f;
	flowJd3.enableMotor = true;
	flowJd3.frequencyHz = 4.0f;
	flowJd3.dampingRatio = 0.7f;


	flowJd4.Initialize(flowBody3, flowBody5, flowBody5->GetPosition(), axis);
	flowJd4.motorSpeed = 25.0f;
	flowJd4.maxMotorTorque = 25.0f;
	flowJd4.enableMotor = true;
	flowJd4.frequencyHz = 4.0f;
	flowJd4.dampingRatio = 1.0f;

	//top
	flowBody6 = this->addNewSpriteFlow(Vec2((winSize.width / 2) + 30, 130), Size(100, 5), b2_dynamicBody, "flowimage", 0);
	flowBody7 = this->addNewSpriteFlow(Vec2(winSize.width / 2, 120), Size(10, 10), b2_dynamicBody, nullptr, 0);
	flowBody8 = this->addNewSpriteFlow(Vec2((winSize.width / 2) + 60, 120), Size(10, 10), b2_dynamicBody, nullptr, 0);


	flowJd5.Initialize(flowBody6, flowBody7, flowBody7->GetPosition(), axis);
	flowJd5.motorSpeed = 20.0f;
	flowJd5.maxMotorTorque = 30.0f;
	flowJd5.enableMotor = true;
	flowJd5.frequencyHz = 4.0f;
	flowJd5.dampingRatio = 1.0f;

	flowJd6.Initialize(flowBody6, flowBody8, flowBody8->GetPosition(), axis);
	flowJd6.motorSpeed = 20.0f;
	flowJd6.maxMotorTorque = 30.0f;
	flowJd6.enableMotor = true;
	flowJd6.frequencyHz = 4.0f;
	flowJd6.dampingRatio = 0.7f;

	m_spring1 = (b2WheelJoint*)_world->CreateJoint(&flowJd1);
	m_spring2 = (b2WheelJoint*)_world->CreateJoint(&flowJd2);
	m_spring3 = (b2WheelJoint*)_world->CreateJoint(&flowJd3);
	m_spring4 = (b2WheelJoint*)_world->CreateJoint(&flowJd4);
	m_spring5 = (b2WheelJoint*)_world->CreateJoint(&flowJd5);
	m_spring6 = (b2WheelJoint*)_world->CreateJoint(&flowJd6);
	//Flow



	//���� ������
	myContactListener = new ContactListener();
	_world->SetContactListener((b2ContactListener*)myContactListener);

	//���� �̹��� �ε�
	ropeSpriteSheet = SpriteBatchNode::create("Sprites/rope_texture.png");
	this->addChild(ropeSpriteSheet);

	//�ٵ� ������ �߰�
	//Add a bunch of ropes
	/*this->createRope(groundBody, b2Vec2((winSize.width / 2) / PTM_RATIO, winSize.height / PTM_RATIO),
		body1,
		body1->GetLocalCenter(),
		1.1f);*/
	return true;
}
b2Body* LSFGame::addNewSpriteAt(Vec2 point)
{
	//Get the sprite frome the sprite sheet
	Sprite* needle = Sprite::create("Sprites/needle.png");
	needle->setAnchorPoint(Vec2(0.5, 0.8));
	this->addChild(needle);

	//Defines the body of needle
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = b2Vec2(point.x / PTM_RATIO, point.y / PTM_RATIO);
	bodyDef.userData = needle;
	bodyDef.linearDamping = 0.3f;
	b2Body* body = _world->CreateBody(&bodyDef);

	//Define the fixture as a shape
	b2FixtureDef fixtureDef;
	b2CircleShape spriteShape;

	spriteShape.m_radius = 0.08;

	fixtureDef.shape = &spriteShape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.2f;
	fixtureDef.restitution = 0.7f;
	fixtureDef.filter.categoryBits = 0x01;
	fixtureDef.filter.groupIndex = -1;

	body->CreateFixture(&fixtureDef);

	return body;
}
b2Body* LSFGame::addNewSpriteAtWater(Vec2 point)
{
	//Get the sprite frome the sprite sheet
	Sprite* water = Sprite::create("Sprites/WaterSplash.png");
	water->setAnchorPoint(Vec2(0.5, 0.8));
	this->addChild(water);

	//Defines the body of water
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = b2Vec2(point.x / PTM_RATIO, point.y / PTM_RATIO);
	bodyDef.userData = water;
	bodyDef.linearDamping = 0.3f;
	b2Body* body = _world->CreateBody(&bodyDef);

	//Define the fixture as a shape
	b2FixtureDef fixtureDef;
	b2CircleShape spriteShape;

	spriteShape.m_radius = 0.03;

	fixtureDef.shape = &spriteShape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.2f;
	fixtureDef.restitution = 0.7f;
	fixtureDef.filter.categoryBits = 0x02;

	body->CreateFixture(&fixtureDef);

	return body;
}
b2Body* LSFGame::addNewSpriteFlow(Vec2 point, Size size, b2BodyType bodytype, const char* spriteName, int type)
{
	//��������Ʈ�� �Ķ���ͷ� �Ѿ�� ��ġ�� �����.
	//Sprite* pSprite = Sprite::createWithTexture(texture, Rect(0, 0, 37, 37));
	//pSprite->setPosition(Vec2(location.x, location.y));
	//this->addChild(pSprite);

	//�ٵ����� ����� �Ӽ����� �����Ѵ�.
	b2BodyDef bodyDef;
	bodyDef.type = bodytype;
	bodyDef.position.Set(point.x / PTM_RATIO, point.y / PTM_RATIO);

	if (spriteName) {
		if (strcmp(spriteName, "flowimage") == 0) {
			int idx = (CCRANDOM_0_1() > .5 ? 0 : 1);
			int idy = (CCRANDOM_0_1() > .5 ? 0 : 1);

			Sprite* flow = Sprite::createWithTexture(texture,
				Rect(32 * idx, 32 * idy, 32, 32));
			flow->setPosition(point);
			this->addChild(flow);

			bodyDef.userData = flow;
		}
		else {
			Sprite* flow = Sprite::create(spriteName);
			flow->setPosition(point);
			this->addChild(flow);

			bodyDef.userData = flow;
		}
	}


	//���忡 �ٵ����� ������ �ٵ� �����.
	b2Body* body = _world->CreateBody(&bodyDef);

	//�ٵ� ������ ���� �Ӽ��� �ٵ��� ����� �����.

	b2FixtureDef fixtureDef;
	b2CircleShape circle;			//�� ���¸� ������ �������� �����Ѵ�.
	b2PolygonShape dynamicBox;

	if (type == 0) {
		dynamicBox.SetAsBox(size.width / 2 / PTM_RATIO, size.height / 2 / PTM_RATIO);

		fixtureDef.shape = &dynamicBox;
	}
	else {
		circle.m_radius = (size.width / 2) / PTM_RATIO;

		fixtureDef.shape = &circle;
	}


	fixtureDef.density = 1.0f;		//�е�
	fixtureDef.friction = 0.2f;		//������ - 0 ~ 1
	fixtureDef.restitution = 0.5f;	//�ݹ߷� - ��ü�� �ٸ� ��ü�� ����� �� ƨ��� ��
	fixtureDef.filter.categoryBits = 0x03;
	fixtureDef.filter.groupIndex = -1;
	body->CreateFixture(&fixtureDef);

	return body;
}

VRope* newRope;
b2RopeJoint* ropeJoint;
void LSFGame::createRope(b2Body* bodyA, b2Vec2 anchorA, b2Body* bodyB, b2Vec2 anchorB, float32 sag)
{
	b2RopeJointDef jd;
	jd.bodyA = bodyA;
	jd.bodyB = bodyB;
	jd.localAnchorA = anchorA;
	jd.localAnchorB = anchorB;

	//Max length of joint = current distance between bodies * sag
	float32 ropeLength = (bodyA->GetWorldPoint(anchorA) - bodyB->GetWorldPoint(anchorB)).Length()*sag;
	if (ropeLength >= 1 && ropeLength <= 3) {
		log("ropeLength: %f", ropeLength);
		log("ropeLength: %f", ropeLength);
		log("ropeLength: %f", ropeLength);
		jd.maxLength = ropeLength;
		ropeJoint = (b2RopeJoint*)_world->CreateJoint(&jd);

		newRope = new VRope(ropeJoint, ropeSpriteSheet);
		ropes->push_back(newRope);

		return;
	}
	else if (ropeLength < 1 || ropeLength>3) {
		log("else if ropeLength: %f", ropeLength);
		log("else if ropeLength: %f", ropeLength);
		log("else if ropeLength: %f", ropeLength);
		jd.maxLength = 3;
		ropeJoint = (b2RopeJoint*)_world->CreateJoint(&jd);

		newRope = new VRope(ropeJoint, ropeSpriteSheet);
		ropes->push_back(newRope);
		return;
	}
	else {

		return;
	}

	//Create Joints..

}
void LSFGame::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
	Layer::draw(renderer, transform, flags);
	_customCommand.init(_globalZOrder);
	_customCommand.func = CC_CALLBACK_0(LSFGame::onDraw, this, transform, flags);
	renderer->addCommand(&_customCommand);
}
void LSFGame::onDraw(const Mat4 &transform, uint32_t flags)
{
	Director* director = Director::getInstance();
	CCASSERT(nullptr != director, "Director is null when seting matrix stack");
	director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
	director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, transform);

	//draw
	GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POSITION);
	_world->DrawDebugData();
	CHECK_GL_ERROR_DEBUG();

	director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
}
void LSFGame::tick(float dt)
{
	int velocityIterations = 8;
	int positionIterations = 3;

	//Step: ���� ���踦 �ùķ��̼��Ѵ�.
	_world->Step(dt, velocityIterations, positionIterations);

	//��� ���� ��ü���� ��ũ�� ����Ʈ�� ����Ǿ� ������ �� �� �ְ� ������ �ִ�.
	//������� ��ü��ŭ ������ �����鼭 �ٵ� ���� ��������Ʈ�� ���⼭ �����Ѵ�.
	for (b2Body *b = _world->GetBodyList(); b; b = b->GetNext())
	{
		if (b->GetUserData() != nullptr) {
			Sprite* spriteData = (Sprite *)b->GetUserData();
			spriteData->setPosition(Vec2(b->GetPosition().x * PTM_RATIO,
				b->GetPosition().y *PTM_RATIO));
			spriteData->setRotation(-1 * CC_RADIANS_TO_DEGREES(b->GetAngle()));
		}
	}
	//RUT(Rope Update Timer)
	if (ropeTickCount == false) {
		//this->schedule(schedule_selector(LSFGame::ropeTick), 0.095);
		this->schedule(schedule_selector(LSFGame::ropeTick));
		ropeTickCount = true;
	}
	//WA(Water Adder)
	if (waterCount < 10) {
		water1 = this->addNewSpriteAtWater(Vec2(10, 120));
		water1 = this->addNewSpriteAtWater(Vec2(12, 120));
		water1 = this->addNewSpriteAtWater(Vec2(winSize.width - 12, 120));
		water1 = this->addNewSpriteAtWater(Vec2(winSize.width - 10, 120));

		water2 = this->addNewSpriteAtWater(Vec2(10, 90));
		water2 = this->addNewSpriteAtWater(Vec2(12, 90));
		water2 = this->addNewSpriteAtWater(Vec2(winSize.width - 12, 90));
		water2 = this->addNewSpriteAtWater(Vec2(winSize.width - 10, 90));

		
		waterCount++;
	}
	if (waterCount < 20) {
		water3 = this->addNewSpriteAtWater(Vec2(14, 50));
		water3 = this->addNewSpriteAtWater(Vec2(12, 50));
		water3 = this->addNewSpriteAtWater(Vec2(10, 50));
		water3 = this->addNewSpriteAtWater(Vec2(winSize.width - 14, 50));
		water3 = this->addNewSpriteAtWater(Vec2(winSize.width - 12, 50));
		water3 = this->addNewSpriteAtWater(Vec2(winSize.width - 10, 50));
		waterCount++;
	}
	//WF(Water flow)
	
	if (flowBody0->GetPosition().x <=0.6)
	{
		m_spring1->SetMotorSpeed(-30.0f);
		m_spring2->SetMotorSpeed(-30.0f);
	}
	else if (flowBody0->GetPosition().x >= 3) {
		m_spring1->SetMotorSpeed(30.0f);
		m_spring2->SetMotorSpeed(30.0f);
	}

	if (flowBody3->GetPosition().x <= 0.6)
	{
		m_spring3->SetMotorSpeed(-25.0f);
		m_spring4->SetMotorSpeed(-25.0f);
	}
	else if (flowBody3->GetPosition().x >= 3) {
		m_spring3->SetMotorSpeed(25.0f);
		m_spring4->SetMotorSpeed(25.0f);
	}

	if (flowBody6->GetPosition().x <= 0.6)
	{
		m_spring5->SetMotorSpeed(-20.0f);
		m_spring6->SetMotorSpeed(-20.0f);
	}
	else if (flowBody6->GetPosition().x >= 3) {
		m_spring5->SetMotorSpeed(20.0f);
		m_spring6->SetMotorSpeed(20.0f);
	}



	//RHC(Rope Health Counter)
	if (ropeHealth == 0) {
		log("Fishing fail!");
		ropeHealth = 10000;
		ropes->clear();
		_world->DestroyJoint(ropeJoint);
		this->unschedule(schedule_selector(LSFGame::ropeTick));
		newRope->removeSprites();
		fishingStat = false;
		ropeTickCount = false;
	}

}
void LSFGame::ropeTick(float dt)
{
	//���� �ùķ��̼�
	std::vector<VRope *>::iterator rope;
	for (rope = ropes->begin(); rope != ropes->end(); ++rope)
	{

		(*rope)->update(dt);
		(*rope)->updateSprites();
	}
}
void LSFGame::ropeTouch(float dt) {
	water->splash(touchRope.x, -100);
}
void ContactListener::BeginContact(b2Contact* contact)
{
	b2Fixture* fixA = contact->GetFixtureA();
	b2Fixture* fixB = contact->GetFixtureB();


	b2Body *bodyA = fixA->GetBody();
	b2Body *bodyB = fixB->GetBody();

	if (bodyA->GetType() == b2_dynamicBody || bodyB->GetType() == b2_dynamicBody) {
		//log("needle & water contact .. ");
		if (ropeHealth > 0 && fishingStat == true)
		{
			ropeHealth--;
			log("ropeHealth :%d", ropeHealth);
		}
	}
}
b2Body* LSFGame::createRopeTipBody()
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.linearDamping = 0.5f;
	b2Body* body = _world->CreateBody(&bodyDef);

	b2FixtureDef circleDef;
	b2CircleShape circle;
	circle.m_radius = 0.4f / PTM_RATIO;
	circleDef.shape = &circle;
	circleDef.density = 10.0f;

	//Since these tips don't have to collide with anything
	//set the mask bits to zero
	circleDef.filter.maskBits = 0;
	body->CreateFixture(&circleDef);
	return body;
}
LSFGame::~LSFGame()
{
	//���带 C++�� new�� ���������Ƿ� ���⼭ �����ش�.
	delete _world;
	_world = nullptr;
}

