#include "LSFGame.h"
#include <ctime>

using namespace cocos2d;

int ropeHealth = 100;
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
	srand(time(nullptr));
	ropes = new std::vector<VRope*>;
	winSize = Director::getInstance()->getWinSize();
	//flow
	
	//flow
	btnCount = 0;
	cbtnCount = 0;
	waterCount = 0;
	fishingStat = false;
	ropeTickCount = false;
	craftSwitch = false;
	
	//스프라이트 추가
	Sprite* backDefault = Sprite::create("Sprites/Game_bg.png");
	backDefault->setAnchorPoint(Vec2::ZERO);
	backDefault->setPosition(Vec2::ZERO);
	//this->addChild(backDefault);
	//!Debug on/off

	auto GameFrameCache = SpriteFrameCache::getInstance();
	GameFrameCache->addSpriteFramesWithJson("Sprites/Game_cloudcut.json");

	back = Sprite::createWithSpriteFrame(GameFrameCache->getSpriteFrameByName("Game_cloudcut 0.png"));
	back->setAnchorPoint(Vec2(0, 1));
	back->setPosition(Vec2(0,winSize.height));
	//this->addChild(back);
	//!Debug on/off

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

	//가방 레이어 추가
	//가방------------------------------------------------------------------------------------------------
	invenLayer = LayerColor::create(Color4B(255, 255, 255, 125),
		winSize.width, winSize.height);
	invenLayer->setAnchorPoint(Vec2::ZERO);
	invenLayer->setPosition(Vec2(0, 0));
	invenLayer->setVisible(false);
	//invenLayer->setScaleY(2.f);
	//invenLayer->setCascadeOpacityEnabled(true);
	this->addChild(invenLayer, 4);

	craftUsel = Sprite::create("Sprites/inventory_bg2.png");
	craftUsel->setAnchorPoint(Vec2::ZERO);
	craftUsel->setPosition(Vec2::ZERO);
	craftUsel->setCascadeOpacityEnabled(true);
	craftUsel->setOpacity(125);
	invenLayer->addChild(craftUsel);

	craftSel = Sprite::create("Sprites/inventory_bg3.png");
	craftSel->setAnchorPoint(Vec2::ZERO);
	craftSel->setPosition(Vec2::ZERO);
	craftSel->setCascadeOpacityEnabled(true);
	craftSel->setOpacity(125);
	craftSel->setVisible(false);
	invenLayer->addChild(craftSel);


	inventory = Sprite::create("Sprites/inventory_bg.png");
	inventory->setAnchorPoint(Vec2::ZERO);
	inventory->setPosition(Vec2::ZERO);
	//inventory->setScale(0.5f,1.5f);
	inventory->setCascadeOpacityEnabled(true);
	inventory->setOpacity(255);
	inventory->setVisible(false);
	invenLayer->addChild(inventory);

	GameFrameCache = SpriteFrameCache::getInstance();
	GameFrameCache->addSpriteFramesWithJson("Sprites/Button_craft.json");

	craft = Sprite::createWithSpriteFrame(GameFrameCache->getSpriteFrameByName("Button_craft 0.png"));
	craft->setAnchorPoint(Vec2(0.5, 0.5));
	craft->setPosition(Vec2(130, winSize.height / 5 - 100));
	craft->setScale(1.5f);
	//craft->setVisible(false);
	invenLayer->addChild(craft);
	//가방----------------------------------------------------------------------------------------------------


	//환경 구조물배치-----------------------------------------------------------------------------------------
	weatherCount = 2;
	auto ShipFrameCache = SpriteFrameCache::getInstance();
	if (weatherCount == 1) {
		ShipFrameCache->addSpriteFramesWithJson("Sprites/Ship_normal.json");
	}
	else if (weatherCount == 2) {
		ShipFrameCache->addSpriteFramesWithJson("Sprites/Ship_windy.json");
	}
	//ShipFrameCache->addSpriteFramesWithJson("Sprites/Ship_normal.json");

	ship = Sprite::createWithSpriteFrame(ShipFrameCache->getSpriteFrameByName("Ship 0.png"));
	ship->setAnchorPoint(Vec2(0.5, 0.1));
	ship->setPosition(Vec2(winSize.width-120, winSize.height/3));
	ship->setLocalZOrder(2);
	ship->setScale(1.5f);
	this->addChild(ship);

	fisherman = Sprite::create("Sprites/Fisherman.png");
	fisherman->setAnchorPoint(Vec2::ZERO);
	fisherman->setPosition(Vec2(-4, 24));
	fisherman->setLocalZOrder(1);
	ship->addChild(fisherman);

	fstUpdate = Sprite::create("Sprites/FishingStat_default.png");
	fstUpdate->setAnchorPoint(Vec2::ZERO);
	fstUpdate->setPosition(Vec2(14, 24));
	fisherman->addChild(fstUpdate);


	//환경 구조물배치----------------------------------------------------------------------------------------

	//메뉴
	btn_inventory = MenuItemImage::create("Sprites/Button_bagclose.png",
		"Sprites/Button_bagopen.png",
		CC_CALLBACK_1(LSFGame::doPushInventory, this));
	btn_inventory->setScale(1.5f);
	inventoryMenu = Menu::create(btn_inventory, nullptr);
	inventoryMenu->setAnchorPoint(Vec2(0.5, 0.5));
	inventoryMenu->setPosition(Vec2(winSize.width-140, winSize.height/5-100));
	inventoryMenu->alignItemsHorizontally();
	this->addChild(inventoryMenu, 4);

	////애니메이션
	//Background
	auto mainAnim = animCreate->CreateAnim("Sprites/Game_cloudcut.json", "Game_cloudcut", 15, 0.1f);
	auto mainAnimate = Animate::create(mainAnim);
	auto repMain = RepeatForever::create(mainAnimate);
	back->runAction(repMain);

	//Ship	(Normal(1), Windy(2), Snowy(3), Rainny(4), ThunderStorm(5))
	ShipStat = 2;

	if(ShipStat == 1){
		if (ship->getNumberOfRunningActions() != 0) {
			ship->cleanup();
		}
		auto shipNormalAnim = animCreate->CreateAnim("Sprites/Ship_normal.json", "Ship", 5, 0.1f);
		auto shipAnimate = Animate::create(shipNormalAnim);
		auto repShip = RepeatForever::create(shipAnimate);
		ship->runAction(repShip);
	}
	else if(ShipStat == 2){
		if (ship->getNumberOfRunningActions() != 0) {
			ship->cleanup();
		}
		auto shipWindyAnim = animCreate->CreateAnim("Sprites/Ship_windy.json", "Ship", 5, 0.1f);
		auto shipAnimate = Animate::create(shipWindyAnim);
		auto repShip = RepeatForever::create(shipAnimate);
		ship->runAction(repShip);

	}
	
	


	//Button_craft
	auto craftAnim = animCreate->CreateAnim("Sprites/Button_craft.json", "Button_craft", 3, 0.1f);
	auto craftAnimate = Animate::create(craftAnim);
	auto repCraft = RepeatForever::create(craftAnimate);
	craft->runAction(repCraft);

	//Weather effect	(Wind, Rain, Snow, Tunder)
	//Rain
	auto rainAnim = animCreate->CreateAnim("Sprites/RainDrop.json", "RainDrop", 3, 0.1f);
	auto rainAnimate = Animate::create(rainAnim);
	auto repRain = RepeatForever::create(rainAnimate);
	//rainDrop->runAction(repRain);

	//Snow
	auto snowAnim = animCreate->CreateAnim("Sprites/SnowDrop.json", "SnowDrop", 3, 0.1f);
	auto snowAnimate = Animate::create(snowAnim);
	auto repSnow = RepeatForever::create(snowAnimate);
	//snowDrop->runAction(repSnow);


	//월드 생성
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
	//싱글 터치 모드로 터치 리스너 등록
	auto listener = EventListenerTouchOneByOne::create();
	//Swallow touches only available in OneByOne mode.
	//핸들링된 터치 이벤트를 터치 이벤트 array에서 지우겠다는 의미다.
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(LSFGame::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(LSFGame::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(LSFGame::onTouchEnded, this);

	// The prioriry of the touch listener is based on the draw order of sprite
	// 터치 리스너의 우선순위를 (노드가) 화면에 그려진 순서대로 한다
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

	//log("onTOuchBegan id = %d, x = %f, y= %f", touch->getID(), touchPoint.x, touchPoint.y);

	//touch check --------------------------------
	bool bTouch_craft = craft->getBoundingBox().containsPoint(touchPoint);
	touchRope = touchPoint; // WaterSplash 발생 위치 지정을 위한 변수
	float splashDelay = touchPoint.y;

	// 게임 화면
	if (cbtnCount == 0) {
		if (cbtnCount == 0 && fishingStat == false) {
			//낚시 시작 전
			needle = this->addNewSpriteAt(touchPoint, "Sprites/needle.png", 1);
			Vec2 fVec = fisherman->convertToWorldSpace(fisherman->getPosition());

			this->createRope(groundBody, b2Vec2((fVec.x + 16) / PTM_RATIO, (fVec.y - 4) / PTM_RATIO),
				needle, needle->GetLocalCenter(), 1.1f);
			//ropeTouchCount = true;
			log("---------------------------Fishing 1");

			log("---------------------------Fishing 2");
			this->scheduleOnce(schedule_selector(LSFGame::waterSplash), splashDelay / 700);
			log("---------------------------Fishing 3");
			startFishing(1);
			log("---------------------------Fishing 3-1");
		}
		if (hangFish == true) {
			log("---------------------------HangFish true -> Touch");
			endFishing(3);
		}
		
		
	}
	// 가방이 열려있고 craft가 선택 됐을 때
	if (bTouch_craft && cbtnCount == 1)
	{
		if (craftSwitch == true)
		{
			craftUsel->setVisible(true);
			craftSel->setVisible(false);
			craftSwitch = false;
			//log("craftSwitch Status: Off", craftSwitch);
		}
		else {
			craftUsel->setVisible(false);
			craftSel->setVisible(true);
			craftSwitch = true;
			//log("craftSwitch Status: On", craftSwitch);
		}

	}

	return true;
}
void LSFGame::onTouchEnded(Touch* touch, Event* event)
{
	auto touchPoint = touch->getLocation();


	//log("%f", test);
	
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
bool LSFGame::createBox2dWorld(bool debug)
{
	//월드 생성 시작-----------------------------------------------------

	//중력의 방향을 결정한다.
	b2Vec2 gravity = b2Vec2(0.0f, -5.0f);

	//월드를 생성한다.
	_world = new b2World(gravity);
	_world->SetAllowSleeping(true);
	_world->SetContinuousPhysics(true);

	//디버그 드로잉 설정
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
	_world->SetAllowSleeping(true);
	_world->SetContinuousPhysics(true);

	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0, 0);
	groundBody = _world->CreateBody(&groundBodyDef);

	b2EdgeShape groundEdge;
	b2FixtureDef boxShapeDef;
	boxShapeDef.shape = &groundEdge;

	//바다 아래
	groundEdge.Set(b2Vec2(0, 3.4f), b2Vec2(winSize.width / PTM_RATIO, 3.4f));
	groundBody->CreateFixture(&boxShapeDef);
	groundEdge.Set(b2Vec2(0, 2.8f), b2Vec2(winSize.width / PTM_RATIO, 2.8f));
	groundBody->CreateFixture(&boxShapeDef);
	groundEdge.Set(b2Vec2(0, 2.2f), b2Vec2(winSize.width / PTM_RATIO, 2.2f));
	groundBody->CreateFixture(&boxShapeDef);
	groundEdge.Set(b2Vec2(0, 1.6f), b2Vec2(winSize.width / PTM_RATIO, 1.6f));
	groundBody->CreateFixture(&boxShapeDef);
	groundEdge.Set(b2Vec2(0, 1.1f), b2Vec2(winSize.width / PTM_RATIO, 1.1f));
	groundBody->CreateFixture(&boxShapeDef);

	//왼쪽
	groundEdge.Set(b2Vec2(0, 0), b2Vec2(0, winSize.height / PTM_RATIO));
	groundBody->CreateFixture(&boxShapeDef);

	//위쪽
	groundEdge.Set(b2Vec2(0, winSize.height / PTM_RATIO),
		b2Vec2(winSize.width / PTM_RATIO, winSize.height / PTM_RATIO));
	groundBody->CreateFixture(&boxShapeDef);

	//오른쪽
	groundEdge.Set(b2Vec2(winSize.width / PTM_RATIO, winSize.height / PTM_RATIO),
		b2Vec2(winSize.width / PTM_RATIO, 0));
	groundBody->CreateFixture(&boxShapeDef);

	//물 범위 가장자리에 틀 생성
	b2BodyDef bottomBodyDef;
	bottomBodyDef.type = b2_staticBody;
	bottomBodyDef.position.Set(winSize.width/2/PTM_RATIO, 1.2f);
	bottomBodyDef.linearDamping = 0.3f;
	
	b2Body* bottomBody;
	bottomBody = _world->CreateBody(&bottomBodyDef);
	b2FixtureDef botfixtureDef;
	b2PolygonShape btmBox;
	btmBox.SetAsBox(3.8f, 0.24f);
	botfixtureDef.shape = &btmBox;
	botfixtureDef.density = 1.0f;
	botfixtureDef.friction = 0;
	botfixtureDef.restitution = 0.0;
	botfixtureDef.filter.groupIndex = -2;
	bottomBody->CreateFixture(&botfixtureDef);

	b2BodyDef btmleftBodyDef;
	btmleftBodyDef.type = b2_staticBody;
	btmleftBodyDef.position.Set(0, 1.4f);
	btmleftBodyDef.linearDamping = 0.3f;
	b2Body* btmleftBody;
	btmleftBody = _world->CreateBody(&btmleftBodyDef);
	b2FixtureDef btmleftfixtureDef;
	b2CircleShape btmleftBox;
	btmleftBox.m_radius = 0.10f;
	btmleftfixtureDef.shape = &btmleftBox;
	btmleftfixtureDef.density = 1.0f;
	btmleftfixtureDef.friction = 0;
	btmleftfixtureDef.restitution = 0.0;
	btmleftfixtureDef.filter.groupIndex = -2;
	btmleftBody->CreateFixture(&btmleftfixtureDef);

	b2BodyDef btmrightBodyDef;
	btmrightBodyDef.type = b2_staticBody;
	btmrightBodyDef.position.Set((winSize.width) / PTM_RATIO, 1.4f);
	btmrightBodyDef.linearDamping = 0.3f;
	b2Body* btmrightBody;
	btmrightBody = _world->CreateBody(&btmrightBodyDef);
	b2FixtureDef btmrightfixtureDef;
	b2CircleShape btmrightBox;
	btmrightBox.m_radius = 0.10f;
	btmrightfixtureDef.shape = &btmrightBox;
	btmrightfixtureDef.density = 1.0f;
	btmrightfixtureDef.friction = 0;
	btmrightfixtureDef.restitution = 0.0;
	btmrightfixtureDef.filter.groupIndex = -2;
	btmrightBody->CreateFixture(&btmrightfixtureDef);

	b2BodyDef leftBodyDef;
	leftBodyDef.type = b2_staticBody;
	leftBodyDef.position.Set(0, 0);
	leftBodyDef.linearDamping = 0.3f;
	b2Body* leftBody;
	leftBody = _world->CreateBody(&leftBodyDef);
	b2FixtureDef leftfixtureDef;
	b2PolygonShape leftBox;
	leftBox.SetAsBox(0.01f, 3.8f);
	leftfixtureDef.shape = &leftBox;
	leftfixtureDef.density = 1.0f;
	leftfixtureDef.friction = 0;
	leftfixtureDef.restitution = 0.0;
	leftfixtureDef.filter.groupIndex = -2;
	leftBody->CreateFixture(&leftfixtureDef);

	b2BodyDef rightBodyDef;
	rightBodyDef.type = b2_staticBody;
	rightBodyDef.position.Set((winSize.width)/ PTM_RATIO, 0);
	rightBodyDef.linearDamping = 0.3f;
	b2Body* rightBody;
	rightBody = _world->CreateBody(&rightBodyDef);
	b2FixtureDef rightfixtureDef;
	b2PolygonShape rightBox;
	rightBox.SetAsBox(0.01f, 3.8f);
	rightfixtureDef.shape = &rightBox;
	rightfixtureDef.density = 1.0f;
	rightfixtureDef.friction = 0;
	rightfixtureDef.restitution = 0.0;
	rightfixtureDef.filter.groupIndex = -2;
	rightBody->CreateFixture(&rightfixtureDef);
	//물 범위 가장자리에 틀 생성 끝
	
	//월드 생성 끝 ---------------------------------------------------

	//Random
	

	//Flow(Water Flow - Fish Start)-----------------------------------
	b2Vec2 axis(0.0f, 1.0f);
	
	//top
	flowRand = rand() % 4 + 1;
	flowBody0 = this->addNewSpriteFlow(Vec2((winSize.width / 2), winSize.height /3-100), Size(100, 5), b2_dynamicBody, flowRand, 0);
	flowBody1 = this->addNewSpriteFlow(Vec2((winSize.width / 2)-40, winSize.height / 3 -120), Size(10, 10), b2_dynamicBody, 0, 0);
	flowBody2 = this->addNewSpriteFlow(Vec2((winSize.width / 2)+40, winSize.height / 3 -120), Size(10, 10), b2_dynamicBody, 0, 0);

	flowJd1.Initialize(flowBody0, flowBody1, flowBody1->GetPosition(), axis);
	flowJd1.motorSpeed = 15.0f;
	flowJd1.maxMotorTorque = 15.0f;
	flowJd1.enableMotor = true;
	flowJd1.frequencyHz = 4.0f;
	flowJd1.dampingRatio = 0.7f;

	flowJd2.Initialize(flowBody0, flowBody2, flowBody2->GetPosition(), axis);
	flowJd2.motorSpeed = 15.0f;
	flowJd2.maxMotorTorque = 15.0f;
	flowJd2.enableMotor = true;
	flowJd2.frequencyHz = 4.0f;
	flowJd2.dampingRatio = 1.0f;

	//center
	flowRand = rand() % 4 + 1;
	flowBody3 = this->addNewSpriteFlow(Vec2((winSize.width / 2), winSize.height/3 -160), Size(100, 10), b2_dynamicBody, flowRand, 0);
	flowBody4 = this->addNewSpriteFlow(Vec2((winSize.width / 2)-40, winSize.height/3 -180), Size(20, 20), b2_dynamicBody, 0, 0);
	flowBody5 = this->addNewSpriteFlow(Vec2((winSize.width / 2)+40, winSize.height/3 -180), Size(20, 20), b2_dynamicBody, 0, 0);

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

	//bottom 1
	flowRand = rand() % 4 + 1;
	flowBody6 = this->addNewSpriteFlow(Vec2((winSize.width / 2), winSize.height/3-220), Size(100, 15), b2_dynamicBody, flowRand, 0);
	flowBody7 = this->addNewSpriteFlow(Vec2((winSize.width / 2)-40, winSize.height/3 - 240), Size(20, 20), b2_dynamicBody, 0, 0);
	flowBody8 = this->addNewSpriteFlow(Vec2((winSize.width / 2)+40, winSize.height/3 - 240), Size(20, 20), b2_dynamicBody, 0, 0);

	flowJd5.Initialize(flowBody6, flowBody7, flowBody7->GetPosition(), axis);
	flowJd5.motorSpeed = 30.0f;
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

	//bottom 2
	flowRand = rand() % 4 + 1;
	flowBody9 = this->addNewSpriteFlow(Vec2((winSize.width / 2) + 50, winSize.height / 3 - 220), Size(100, 15), b2_dynamicBody, flowRand, 0);
	flowBody10 = this->addNewSpriteFlow(Vec2((winSize.width / 2) + 10, winSize.height / 3 - 240), Size(20, 20), b2_dynamicBody, 0, 0);
	flowBody11 = this->addNewSpriteFlow(Vec2((winSize.width / 2) + 90, winSize.height / 3 - 240), Size(20, 20), b2_dynamicBody, 0, 0);

	flowJd7.Initialize(flowBody9, flowBody10, flowBody10->GetPosition(), axis);
	flowJd7.motorSpeed = 30.0f;
	flowJd7.maxMotorTorque = 30.0f;
	flowJd7.enableMotor = true;
	flowJd7.frequencyHz = 4.0f;
	flowJd7.dampingRatio = 1.0f;

	flowJd8.Initialize(flowBody9, flowBody11, flowBody11->GetPosition(), axis);
	flowJd8.motorSpeed = 20.0f;
	flowJd8.maxMotorTorque = 30.0f;
	flowJd8.enableMotor = true;
	flowJd8.frequencyHz = 4.0f;
	flowJd8.dampingRatio = 0.7f;

	m_spring1 = (b2WheelJoint*)_world->CreateJoint(&flowJd1);
	m_spring2 = (b2WheelJoint*)_world->CreateJoint(&flowJd2);
	m_spring3 = (b2WheelJoint*)_world->CreateJoint(&flowJd3);
	m_spring4 = (b2WheelJoint*)_world->CreateJoint(&flowJd4);
	m_spring5 = (b2WheelJoint*)_world->CreateJoint(&flowJd5);
	m_spring6 = (b2WheelJoint*)_world->CreateJoint(&flowJd6);
	m_spring7 = (b2WheelJoint*)_world->CreateJoint(&flowJd7);
	m_spring8 = (b2WheelJoint*)_world->CreateJoint(&flowJd8);

	//Flow(Water Flow - Fish End)-------------------------------------

	//컨택 리스너
	myContactListener = new ContactListener();
	_world->SetContactListener((b2ContactListener*)myContactListener);

	//밧줄 이미지 로드
	ropeSpriteSheet = SpriteBatchNode::create("Sprites/rope_texture.png");
	this->addChild(ropeSpriteSheet);

	//배
	b2BodyDef shipBodyDef;
	shipBodyDef.type = b2_staticBody; 
	shipBodyDef.position.Set((winSize.width + 470) / 2 / PTM_RATIO, ((winSize.height / 3)-60) / PTM_RATIO);
	shipBodyDef.userData = ship;

	b2Body* shipBody = _world->CreateBody(&shipBodyDef);
	b2FixtureDef shipFixtureDef;
	b2PolygonShape shipBox;
	shipBox.SetAsBox(0.8f, 0.2f);
	shipFixtureDef.shape = &shipBox;
	shipFixtureDef.density = 1.0f;		//밀도
	shipFixtureDef.friction = 0.2f;		//마찰력 - 0 ~ 1
	shipFixtureDef.restitution = 0.5f;	//반발력 - 물체가 다른 물체에 닿았을 때 튕기는 값
	shipFixtureDef.filter.categoryBits = 0x01;
	shipFixtureDef.filter.groupIndex = -1;
	
	shipBody->CreateFixture(&shipFixtureDef);
	
	return true;
}
b2Body* LSFGame::addNewSpriteAt(Vec2 point, const std::string & imagepath, int tag)
{
	b2BodyDef bodyDef;
	
	
	b2CircleShape spriteShape;
	//Get the sprite frome the sprite sheet
	Sprite* needle = Sprite::create(imagepath);
	needle->setAnchorPoint(Vec2(0.5, 0.8));
	this->addChild(needle);

	
	//Defines the body of needle
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = b2Vec2(point.x / PTM_RATIO, point.y / PTM_RATIO);
	bodyDef.userData = needle;
	bodyDef.linearDamping = 0.3f;
	needlebody = _world->CreateBody(&bodyDef);
	if (tag == 1) {
		spriteShape.m_radius = 0.1;
		needlefixtureDef.shape = &spriteShape;
		needlefixtureDef.density = 1.0f;
		needlefixtureDef.friction = 0.2f;
		needlefixtureDef.restitution = 0.4f;
		needlefixtureDef.filter.categoryBits = 0x01;
		needlefixtureDef.filter.maskBits = 0x03;
		needlefixtureDef.filter.groupIndex = -1;
	}

	needlebody->CreateFixture(&needlefixtureDef);

	return needlebody;
}
int flowCount = 0;
b2Body* LSFGame::addNewSpriteFlow(Vec2 point, Size size, b2BodyType bodytype, int flowtype, int type)
{
	//스프라이트를 파라미터로 넘어온 위치에 만든다.
	//Sprite* pSprite = Sprite::createWithTexture(texture, Rect(0, 0, 37, 37));
	//pSprite->setPosition(Vec2(location.x, location.y));
	//this->addChild(pSprite);

	//바디데프를 만들고 속성들을 지정한다.
	b2BodyDef bodyDef;
	bodyDef.type = bodytype;
	bodyDef.position.Set(point.x / PTM_RATIO, point.y / PTM_RATIO);

	if (flowtype) {
		if (flowtype == 1) {
			//int idx = (CCRANDOM_0_1() > .5 ? 0 : 1);
			//int idy = (CCRANDOM_0_1() > .5 ? 0 : 1);
			auto flowSprite = Sprite::createWithTexture(texture = Director::getInstance()->getTextureCache()->addImage("Sprites/Fishes/Fish011.png"),
				Rect(0, 0, 24, 16));
			flow.pushBack(flowSprite);
			flow.at(flowCount)->setPosition(point);
			flow.at(flowCount)->setTag(flowCount);
			this->addChild(flow.at(flowCount));

			bodyDef.userData = flow.at(flowCount);
			flowCount++;
		}
		else if (flowtype == 2) {
			auto flowSprite = Sprite::createWithTexture(texture = Director::getInstance()->getTextureCache()->addImage("Sprites/Fishes/Fish004.png"),
				Rect(0, 0, 34, 34));
			flow.pushBack(flowSprite);
			flow.at(flowCount)->setPosition(point);
			flow.at(flowCount)->setTag(flowCount);
			this->addChild(flow.at(flowCount));

			bodyDef.userData = flow.at(flowCount);
			flowCount++;
		}
		else if (flowtype == 3) {
			auto flowSprite = Sprite::createWithTexture(texture = Director::getInstance()->getTextureCache()->addImage("Sprites/Fishes/Fish021.png"),
				Rect(0, 0, 34, 34));
			flow.pushBack(flowSprite);
			flow.at(flowCount)->setPosition(point);
			flow.at(flowCount)->setTag(flowCount);
			this->addChild(flow.at(flowCount));

			bodyDef.userData = flow.at(flowCount);
			flowCount++;
		}
		else if (flowtype == 4) {
			auto flowSprite = Sprite::createWithTexture(texture = Director::getInstance()->getTextureCache()->addImage("Sprites/Fishes/Fish117.png"),
				Rect(0, 0, 34, 34));
			flow.pushBack(flowSprite);
			flow.at(flowCount)->setPosition(point);
			flow.at(flowCount)->setTag(flowCount);
			this->addChild(flow.at(flowCount));

			bodyDef.userData = flow.at(flowCount);
			flowCount++;
		}

	}
	//월드에 바디데프의 정보로 바디를 만든다.
	b2Body* body = _world->CreateBody(&bodyDef);

	//바디에 적용할 물리 속성용 바디의 모양을 만든다.
	b2FixtureDef fixtureDef;
	b2CircleShape circle;			//원 형태를 선택해 반지름을 지정한다.
	b2PolygonShape dynamicBox;

	if (type == 0) {
		dynamicBox.SetAsBox(size.width / 2 / PTM_RATIO, size.height / 2 / PTM_RATIO);

		fixtureDef.shape = &dynamicBox;
	}
	else {
		circle.m_radius = (size.width / 2) / PTM_RATIO;

		fixtureDef.shape = &circle;
	}

	fixtureDef.density = 1.0f;		//밀도
	fixtureDef.friction = 0.2f;		//마찰력 - 0 ~ 1
	fixtureDef.restitution = 0.5f;	//반발력 - 물체가 다른 물체에 닿았을 때 튕기는 값
	fixtureDef.filter.categoryBits = 0x03;
	fixtureDef.filter.groupIndex = -2;
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
	ropeLength = (bodyA->GetWorldPoint(anchorA) - bodyB->GetWorldPoint(anchorB)).Length()*sag;
	log("ropeLength: %f", ropeLength);
	if (ropeLength >= 1 && ropeLength <= 5) {
		log("ropeLength: %f", ropeLength);
		log("ropeLength: %f", ropeLength);
		log("ropeLength: %f", ropeLength);
		jd.maxLength = ropeLength;
		ropeJoint = (b2RopeJoint*)_world->CreateJoint(&jd);

		newRope = new VRope(ropeJoint, ropeSpriteSheet);
		ropes->push_back(newRope);

		return;
	}
	else if (ropeLength < 1 || ropeLength>5) {
		log("else if ropeLength: %f", ropeLength);
		log("else if ropeLength: %f", ropeLength);
		log("else if ropeLength: %f", ropeLength);
		jd.maxLength = 5;
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

	//Step: 물리 세계를 시뮬레이션한다.
	_world->Step(dt, velocityIterations, positionIterations);

	//모든 물리 객체들은 링크드 리스트에 저장되어 참조해 볼 수 있게 구현돼 있다.
	//만들어진 객체만큼 루프를 돌리면서 바디에 붙인 스프라이트를 여기서 제어한다.
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
	/*
	//WA(Water Adder)
	if (waterCount < 30) {
		//top
		water1 = this->addNewSpriteAt(Vec2((winSize.width / 2), (winSize.height / 3 - 110)), "Sprites/WaterSplash.png",2);
		water1 = this->addNewSpriteAt(Vec2((winSize.width / 2) - 2, (winSize.height / 3 - 110)), "Sprites/WaterSplash.png", 2);
		//center
		water2 = this->addNewSpriteAt(Vec2((winSize.width / 2), (winSize.height / 3 - 170)), "Sprites/WaterSplash.png", 2);
		water2 = this->addNewSpriteAt(Vec2((winSize.width / 2) - 2, (winSize.height / 3 - 170)), "Sprites/WaterSplash.png", 2);
		//bottom
		water3 = this->addNewSpriteAt(Vec2((winSize.width / 2), (winSize.height / 3 - 230)), "Sprites/WaterSplash.png", 2);
		water3 = this->addNewSpriteAt(Vec2((winSize.width / 2) - 2, (winSize.height / 3 - 230)), "Sprites/WaterSplash.png", 2);
		water3 = this->addNewSpriteAt(Vec2((winSize.width / 2), (winSize.height / 3 - 230)), "Sprites/WaterSplash.png", 2);
		water3 = this->addNewSpriteAt(Vec2((winSize.width / 2) - 2, (winSize.height / 3 - 230)), "Sprites/WaterSplash.png", 2);
		waterCount++;
	}
	*/

	//WF(Water flow Start)---------------------------------------
	//log("flowbody %f", flowBody0->GetPosition().x);
	if (flowBody0->GetPosition().x <=0.6)
	{
		m_spring1->SetMotorSpeed(-30.0f);
		m_spring2->SetMotorSpeed(-30.0f);
		flow.at(0)->setFlippedX(true);
		
	}
	else if (flowBody0->GetPosition().x >= 6.6) {
		m_spring1->SetMotorSpeed(30.0f);
		m_spring2->SetMotorSpeed(30.0f);
		flow.at(0)->setFlippedX(false);
	}

	if (flowBody3->GetPosition().x <= 0.6)
	{
		m_spring3->SetMotorSpeed(-25.0f);
		m_spring4->SetMotorSpeed(-25.0f);
		flow.at(1)->setFlippedX(true);
	}
	else if (flowBody3->GetPosition().x >= 6.6) {
		m_spring3->SetMotorSpeed(25.0f);
		m_spring4->SetMotorSpeed(25.0f);
		flow.at(1)->setFlippedX(false);
	}

	if (flowBody6->GetPosition().x <= 0.6)
	{
		m_spring5->SetMotorSpeed(-20.0f);
		m_spring6->SetMotorSpeed(-20.0f);
		flow.at(2)->setFlippedX(true);
	}
	else if (flowBody6->GetPosition().x >= 6.6) {
		m_spring5->SetMotorSpeed(20.0f);
		m_spring6->SetMotorSpeed(20.0f);
		flow.at(2)->setFlippedX(false);
	}

	if (flowBody9->GetPosition().x <= 0.6)
	{
		m_spring7->SetMotorSpeed(-20.0f);
		m_spring8->SetMotorSpeed(-20.0f);
		flow.at(3)->setFlippedX(true);
	}
	else if (flowBody9->GetPosition().x >= 6.6) {
		m_spring7->SetMotorSpeed(20.0f);
		m_spring8->SetMotorSpeed(20.0f);
		flow.at(3)->setFlippedX(false);
	}
	//WF(Water flow End)-----------------------------------------

	//RHC(Rope Health Counter Start)-----------------------------
	if (ropeHealth == 0) {
		ropeRemove(2);
	}
	//RHC(Rope Health Counter End)-------------------------------
		
}

void LSFGame::startFishing(float dt)
{
	log("---------------------------Fishing 4");
	fishingStat = true;
	log("ropeLength: %f", ropeLength);
	if(ropeLength >= 6)
	{
		randomTime = random(10,20);
		catchTime = random(8, randomTime - 3);
		ropeHealth = ropeHealth * 12;
	}
	else if (ropeLength > 4 && ropeLength < 6)
	{
		randomTime = random(8, 15);
		catchTime = random(6, randomTime - 3);
		ropeHealth = ropeHealth * 10;
	}
	else if (ropeLength >= 3 && ropeLength <= 4) 
	{
		randomTime = random(5,10);
		catchTime = random(3, randomTime - 3);
		ropeHealth = ropeHealth * 5;
	}
	else if (ropeLength >= 1 && ropeLength < 3) {
		randomTime = random(3 , 10);
		catchTime = random(3, randomTime - 3);
		ropeHealth = ropeHealth * 5;
	}
	fstChange(1);
	timer = randomTime;
	this->schedule(schedule_selector(LSFGame::timerFishing), 1.f);
	log("---------------------------Fishing 4-END");
	//Success
}
void LSFGame::timerFishing(float dt)
{
	log("timerFishing: %d", timer);
	log("catchTime: %d", catchTime);
	if (--timer == 0) {
		endFishing(1);
	}
	if (timer != 0) {
		if (catchTime-- == 0) {
			//catchTime = random(timer-1, timer);
			log("Enable catch Fish !!!");
			hangFish = true;
			fstChange(2);
		}
		if (catchTime < -5) {
			log("Disable catch Fish !!!");
			fstChange(4);
			hangFish = false;
		}
	}
	log("---------------------------Fishing 5");
}
void LSFGame::endFishing(float dt) 
{
	log("EndFishing");
	this->unschedule(schedule_selector(LSFGame::timerFishing));
	log("---------------------------Fishing 6");
	ropeRemove(dt);
}
void LSFGame::fstChange(int type)
{

	//FishingStat
	if (fstUpdate->numberOfRunningActions() == 0) {

		if (type == 1) {
			auto fstNormalAnim = animCreate->CreateAnim("Sprites/FishingStat_normal.json", "FishingStat", 4, 0.1f);
			auto fstNormalAnimate = Animate::create(fstNormalAnim);
			repFstNormal = RepeatForever::create(fstNormalAnimate);
			fstUpdate->runAction(repFstNormal);
			log("fstUpdate Type 1 Activate !!");
		}
		if (type == 2) {
			auto fstHangAnim = animCreate->CreateAnim("Sprites/FishingStat_hang.json", "FishingStat", 4, 0.1f);
			auto fstHangAnimate = Animate::create(fstHangAnim);
			repFstHang = Repeat::create(fstHangAnimate, 1);
			fstUpdate->runAction(repFstHang);
			log("fstUpdate Type 2 Activate !!");
		}
		if (type == 3) {
			auto fstSuccessAnim = animCreate->CreateAnim("Sprites/FishingStat_success.json", "FishingStat", 4, 0.1f);
			auto fstSuccessAnimate = Animate::create(fstSuccessAnim);
			repFstSuccess = Repeat::create(fstSuccessAnimate, 1);
			fstUpdate->runAction(repFstSuccess);
			log("fstUpdate Type 3 Activate !!");
		}
		if (type == 4) {
			auto fstFailAnim = animCreate->CreateAnim("Sprites/FishingStat_fail.json", "FishingStat", 4, 0.1f);
			auto fstFailAnimate = Animate::create(fstFailAnim);
			repFstFail = Repeat::create(fstFailAnimate, 1);
			fstUpdate->runAction(repFstFail);
			log("fstUpdate Type 4 Activate !!");
		}
	}
	else {
		if (fstCount == 1)
		{
			fstCount = 0;
			return;
		}
		log("fstUpdate stopAllAction!!");
		fstUpdate->stopAllActions();
		fstCount++;
		fstChange(type);

	}
}

void LSFGame::ropeRemove(int type) 
{
	log("---------------------------Fishing 7");
	if (type == 1) {
		
		log("---------------------------Fishing 7-1");
		fstChange(4);
		log("Fishing fail!");
		log("TIME OVER");
		
	}
	else if (type == 2) {
		log("---------------------------Fishing 7-2");
		fstChange(4);
		log("Fishing fail!");
		log("ropeHealth ZERO");
		this->unschedule(schedule_selector(LSFGame::timerFishing));
	}
	else if (type == 3) {
		log("---------------------------Fishing 7-3");
		this->unschedule(schedule_selector(LSFGame::timerFishing));
		fstChange(3);
		log("Fishing Success");
		
	}
	
	ropeHealth = 100;
	ropes->clear();
	_world->DestroyJoint(ropeJoint);
	this->unschedule(schedule_selector(LSFGame::ropeTick));
	newRope->removeSprites();
	needle->DestroyFixture(needle->GetFixtureList());

	fishingStat = false;
	hangFish = false;
	ropeTickCount = false;
}
void LSFGame::ropeTick(float dt)
{
	//밧줄 시뮬레이션
	std::vector<VRope *>::iterator rope;
	for (rope = ropes->begin(); rope != ropes->end(); ++rope)
	{

		(*rope)->update(dt);
		(*rope)->updateSprites();
	}
}
void LSFGame::waterSplash(float dt) {
	/*WaterSplash Effect Sound 추가 예정*/
	water->splash(touchRope.x, -100);
}
void ContactListener::BeginContact(b2Contact* contact)
{
	b2Fixture* fixA = contact->GetFixtureA();
	b2Fixture* fixB = contact->GetFixtureB();

	b2Body *bodyA = fixA->GetBody();
	b2Body *bodyB = fixB->GetBody();
	
	//b2Log

	if (bodyA->GetType() == b2_dynamicBody || bodyB->GetType() == b2_dynamicBody) {
		if (ropeHealth > 0 && fishingStat == true)
		{
			ropeHealth--;
			//log("ropeHealth :%d", ropeHealth);
		}
	}
}
int LSFGame::statusCheck(const std::string & kindof)
{
	if (kindof == "ship")
	{

	}
	return 0;
}
LSFGame::~LSFGame()
{
	//월드를 C++의 new로 생성했으므로 여기서 지워준다.
	delete _world;
	_world = nullptr;
}

