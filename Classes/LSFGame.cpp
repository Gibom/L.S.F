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

	ropes = new std::vector<VRope*>;
	winSize = Director::getInstance()->getWinSize();
	btnCount = 0;
	cbtnCount = 0;
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

	fisherman = Sprite::create("Sprites/Fisherman.png");
	fisherman->setAnchorPoint(Vec2::ZERO);
	fisherman->setPosition(Vec2(-4, 24));
	fisherman->setZOrder(1);
	ship->addChild(fisherman);



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


	//���� ����
	if (this->createBox2dWorld(true))
	{
		this->schedule(schedule_selector(LSFGame::tick));
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

	_eventDispatcher->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);

	Layer::onExit();
}
bool LSFGame::onTouchBegan(Touch* touch, Event* event)
{
	Vec2 touchPoint = touch->getLocation();

	log("onTOuchBegan id = %d, x = %f, y= %f", touch->getID(), touchPoint.x, touchPoint.y);

	//touch check --------------------------------
	bool bTouch_craft = craft->getBoundingBox().containsPoint(touchPoint);
	bool bTouch_mode; //��� ����ġ ���� �� ���

	// ���� ȭ��
	if (cbtnCount == 0) {
		b2Body* body1 = this->addNewSpriteAt(touchPoint);
		
		Vec2 fVec = fisherman->convertToWorldSpace(fisherman->getPosition());

		this->createRope(groundBody,
			b2Vec2((fVec.x+16) / PTM_RATIO, (fVec.y-4) / PTM_RATIO),
			body1,
			body1->GetLocalCenter(),
			1.1f);
		log("fVec X: %f", fVec.x);
		log("fVec Y: %f", fVec.y);
		log("winSize X:  %f", winSize.width) ;
		log("winSize X:  %f", winSize.height);
		log("rope X:  %f", (winSize.width / 2) / PTM_RATIO);
		log("rope Y:  %f", winSize.height / PTM_RATIO);
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
bool LSFGame::createBox2dWorld(bool debug)
{
	//���� ���� ����-----------------------------------------------------

	//�߷��� ������ �����Ѵ�.
	b2Vec2 gravity = b2Vec2(0.0f, -30.0f);

	//���带 �����Ѵ�.
	_world = new b2World(gravity);
	_world->SetAllowSleeping(true);
	_world->SetContinuousPhysics(true);

	//����� ����� ����
	if (debug) {
		//���� : ���� ���� ��� �ϴ� ��
		//ȸ�� : ���� ���� ����� ���� ��
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

	//�Ʒ���
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

	//���� �̹��� �ε�
	ropeSpriteSheet = SpriteBatchNode::create("Sprites/rope_texture.png");
	this->addChild(ropeSpriteSheet);

	//������ �߰�
	//b2Body* body1 = this->addNewSpriteAt(Vec2(winSize.width / 2, winSize.height * 2 / 3));

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
	Sprite* sprite = Sprite::create("Sprites/Fishes/Fish098.png");
	this->addChild(sprite);

	//Defines the body of your candy
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = b2Vec2(point.x / PTM_RATIO, point.y / PTM_RATIO);
	bodyDef.userData = sprite;
	bodyDef.linearDamping = 0.3f;
	b2Body* body = _world->CreateBody(&bodyDef);

	//Define the fixture as a polygon
	b2FixtureDef fixtureDef;
	b2PolygonShape spriteShape;

	b2Vec2 verts[] = {
		b2Vec2(-7.6f / PTM_RATIO, -34.4f / PTM_RATIO),
		b2Vec2(8.3f / PTM_RATIO, -34.4f / PTM_RATIO),
		b2Vec2(15.55f / PTM_RATIO, -27.15f / PTM_RATIO),
		b2Vec2(13.8f / PTM_RATIO, 23.05f / PTM_RATIO),
		b2Vec2(-3.35f / PTM_RATIO, 35.25f / PTM_RATIO),
		b2Vec2(-16.25f / PTM_RATIO, 25.55f / PTM_RATIO),
		b2Vec2(-15.55f / PTM_RATIO, -23.95f / PTM_RATIO),
	};
	spriteShape.Set(verts, 7);

	fixtureDef.shape = &spriteShape;
	fixtureDef.density = 30.0f;
	fixtureDef.filter.categoryBits = 0x01;
	fixtureDef.filter.maskBits = 0x01;

	body->CreateFixture(&fixtureDef);

	return body;
}
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
		jd.maxLength = ropeLength;
		b2RopeJoint* ropeJoint = (b2RopeJoint*)_world->CreateJoint(&jd);

		VRope* newRope = new VRope(ropeJoint, ropeSpriteSheet);
		ropes->push_back(newRope);
		log("ropeLength: %f", ropeLength);
		log("ropeLength: %f", ropeLength);
		log("ropeLength: %f", ropeLength);
		return;
	}
	else if(ropeLength<1||ropeLength>3){
		jd.maxLength = 2;
		b2RopeJoint* ropeJoint = (b2RopeJoint*)_world->CreateJoint(&jd);

		VRope* newRope = new VRope(ropeJoint, ropeSpriteSheet);
		ropes->push_back(newRope);
		log("else if ropeLength: %f", ropeLength);
		log("else if ropeLength: %f", ropeLength);
		log("else if ropeLength: %f", ropeLength);
		return;
	}
	else {
		log("else ropeLength: %f", ropeLength);
		log("else ropeLength: %f", ropeLength);
		log("else ropeLength: %f", ropeLength);
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
	//������ ��ġ�� �̿��� �׷��� ��ġ�� �����Ѵ�.

	//velocityIterations : �ٵ���� ���������� �̵���Ű�� ���� �ʿ��� �浹���� �ݺ������� ���
	//positionIterations : ����Ʈ �и��� ��ħ ������ ���̱� ���� �ٵ��� ��ġ�� �ݺ������� ����
	//���� Ŭ���� ��Ȯ�� ������ ���������� ������ ��������.

	//������Ʈ ���� �� �⺻��
	//int velocityIterations = 8;
	//int positionIterations = 1;

	//�Ŵ��� ���� ���尪
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
	//���� �ùķ��̼�
	std::vector<VRope *>::iterator rope;
	for (rope = ropes->begin(); rope != ropes->end(); ++rope)
	{
		(*rope)->update(dt);
		(*rope)->updateSprites();
	}
}

LSFGame::~LSFGame()
{
	//���带 C++�� new�� ���������Ƿ� ���⼭ �����ش�.
	delete _world;
	_world = nullptr;
}