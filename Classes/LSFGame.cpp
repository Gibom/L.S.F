#include "LSFGame.h"
#include <ctime>

using namespace cocos2d;

int ropeHealth = 500;
bool fishingStat;

static void printProperties(Properties* properties, int indent);
VRope* newRope;
b2RopeJoint* ropeJoint;

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
	listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(LSFGame::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(LSFGame::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(LSFGame::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	ropes = new std::vector<VRope*>;
	winSize = Director::getInstance()->getWinSize();

	this->schedule(schedule_selector(LSFGame::WorldTimer), 2.5f);	//기본값 duration 2.5, 밸런스 조정 필요

	cbtnCount = 0;
	waterCount = 0;
	btnCount = false;
	modeSwitch = false;
	touchCount = false;
	fishingStat = false;
	ropeTickCount = false;
	craftSwitch = false;
	dayChanger = 0;	// 초기값(0), 아침(1), 점심(2), 저녁(3)
	wtInit = random(1, 340);
	wTime += wtInit; // 시간값 초기화

	invNull = Sprite::create("Sprites/Icon.png");
	invNull->setTag(0);
	this->addChild(invNull);

	this->scheduleOnce(schedule_selector(LSFGame::touchCounter), 2.f); //초기 진입시 터치 2초후에 활성화

	//상태표시 레이어
	StatLayer = LayerColor::create(Color4B(255, 255, 255, 0), winSize.width, winSize.height);
	StatLayer->setAnchorPoint(Vec2::ZERO);
	StatLayer->setPosition(Vec2(0, 0));
	StatLayer->setVisible(true);
	this->addChild(StatLayer, 5);

	WStatBack = Sprite::create("Sprites/StatBar.png");
	WStatBack->setAnchorPoint(Vec2(0, 1));
	WStatBack->setPosition(Vec2(0, winSize.height));
	StatLayer->addChild(WStatBack);


	//수동모드 레이어
	manualLayer = LayerColor::create(Color4B(255, 255, 255, 0), winSize.width, winSize.height);
	manualLayer->setAnchorPoint(Vec2::ZERO);
	manualLayer->setPosition(Vec2(0, 0));
	manualLayer->setVisible(true);
	this->addChild(manualLayer, 4);

	//프로그레스바 레이어
	progressLayer = LayerColor::create(Color4B(255, 255, 255, 0), winSize.width, winSize.height);
	progressLayer->setAnchorPoint(Vec2::ZERO);
	progressLayer->setVisible(true);
	this->addChild(progressLayer, 4);

	prgHangBack = Sprite::create("Sprites/prgHangLayer.png");
	prgHangBack->setPosition(Vec2(winSize.width / 2, winSize.height / 2 + 155));
	progressLayer->addChild(prgHangBack);

	prgFailBack = Sprite::create("Sprites/prgFailLayer.png");
	prgFailBack->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
	progressLayer->addChild(prgFailBack);

	//조이스틱
	joystick = Joystick::create();
	joystick->setVisible(false);
	this->addChild(joystick, 4);

	//스프라이트 추가
	backDefault = Sprite::create("Sprites/Game_bg.png");
	backDefault->setAnchorPoint(Vec2::ZERO);
	backDefault->setPosition(Vec2::ZERO);
	this->addChild(backDefault);
	//!Debug on/off

	auto GameFrameCache = SpriteFrameCache::getInstance();
	GameFrameCache->addSpriteFramesWithJson("Sprites/Game_cloudcut.json");

	back = Sprite::createWithSpriteFrame(GameFrameCache->getSpriteFrameByName("Game_cloudcut 0.png"));
	back->setAnchorPoint(Vec2(0, 1));
	back->setScaleY(0.8f);
	back->setPosition(Vec2(0, winSize.height - 20));
	this->addChild(back, 2);
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
	invenLayer = LayerColor::create(Color4B(255, 255, 255, 0),
		winSize.width, winSize.height);
	invenLayer->setAnchorPoint(Vec2::ZERO);
	invenLayer->setPosition(Vec2(0, 0));
	invenLayer->setVisible(false);
	this->addChild(invenLayer, 4);

	craftUsel = Sprite::create("Sprites/inventory_guide.png");
	craftUsel->setAnchorPoint(Vec2::ZERO);
	craftUsel->setPosition(Vec2::ZERO);
	craftUsel->setCascadeOpacityEnabled(true);
	craftUsel->setOpacity(125);
	invenLayer->addChild(craftUsel);

	craftSel = Sprite::create("Sprites/inventory_guide_craft.png");
	craftSel->setAnchorPoint(Vec2::ZERO);
	craftSel->setPosition(Vec2::ZERO);
	craftSel->setCascadeOpacityEnabled(true);
	craftSel->setOpacity(125);
	craftSel->setVisible(false);
	invenLayer->addChild(craftSel);

	
	inv1 = MenuItemImage::create("Sprites/inventory_tool_sel.png", "Sprites/inventory_tool_usel.png",
		CC_CALLBACK_1(LSFGame::doPushInvTab, this));
	inv1->setTag(10);
	inv2 = MenuItemImage::create("Sprites/inventory_Expand_sel.png", "Sprites/inventory_Expand_usel.png",
		CC_CALLBACK_1(LSFGame::doPushInvTab, this));
	inv2->setTag(20);
	inv3 = MenuItemImage::create("Sprites/inventory_Fish_sel.png", "Sprites/inventory_Fish_usel.png",
		CC_CALLBACK_1(LSFGame::doPushInvTab, this));
	inv3->setTag(30);

	invTab = Menu::create(inv1, inv2, inv3, nullptr);
	invTab->setAnchorPoint(Vec2::ZERO);
	invTab->setPosition(Vec2(invTab->getPosition().x - 215, invTab->getPosition().y + 422));
	invTab->alignItemsHorizontally();
	invTab->setVisible(false);
	invenLayer->addChild(invTab, 4);


	GameFrameCache = SpriteFrameCache::getInstance();
	GameFrameCache->addSpriteFramesWithJson("Sprites/inventory_open.json");

	invOpen = Sprite::createWithSpriteFrame(GameFrameCache->getSpriteFrameByName("inventory_open 0.png"));
	invOpen->setAnchorPoint(Vec2::ZERO);
	invOpen->setPosition(Vec2(0, 110));
	invOpen->setCascadeOpacityEnabled(true);
	invOpen->setOpacity(255);
	invenLayer->addChild(invOpen);


	GameFrameCache = SpriteFrameCache::getInstance();
	GameFrameCache->addSpriteFramesWithJson("Sprites/Button_craft.json");

	craft = Sprite::createWithSpriteFrame(GameFrameCache->getSpriteFrameByName("Button_craft 0.png"));
	craft->setAnchorPoint(Vec2(0.5, 0.5));
	craft->setPosition(Vec2(130, winSize.height / 5 - 100));
	craft->setScale(1.5f);
	//craft->setVisible(false);
	invenLayer->addChild(craft);

	btnCraft = Sprite::create("Sprites/Button_combine.png");
	btnCraft->setAnchorPoint(Vec2::ZERO);
	btnCraft->setPosition(Vec2(198, 340));
	btnCraft->setVisible(false);
	invenLayer->addChild(btnCraft);

	craftTmp1 = Sprite::create("Sprites/Craft_selected.png");
	craftTmp1->setAnchorPoint(Vec2::ZERO);
	craftTmp1->setPosition(Vec2(20, 15));
	craftTmp1->setScale(1.5f);
	btnCraft->addChild(craftTmp1);

	craftTmp2 = Sprite::create("Sprites/Craft_selected.png");
	craftTmp2->setAnchorPoint(Vec2::ZERO);
	craftTmp2->setPosition(Vec2(193, 15));
	craftTmp2->setScale(1.5f);
	btnCraft->addChild(craftTmp2);

	inv = new Inventory;

	//가방 테이블 생성 
	//장비 탭
	for (int invRow = 0; invRow < 8; invRow++)
	{
		invTable.push_back(inv->CreateTable(invRow));
		invenLayer->addChild(invTable.at(invRow));
		invTable.at(invRow)->setVisible(false);
		if (invRow == 7)
		{
			tableComplete = true;
		}
	}
	//소모품탭
	for (int invRow = 8; invRow < 16; invRow++)
	{
		invTable.push_back(inv->CreateTable(invRow));
		invenLayer->addChild(invTable.at(invRow));
		invTable.at(invRow)->setVisible(false);
	}
	//물고기탭
	for (int invRow = 16; invRow < 25; invRow++)
	{
		invTable.push_back(inv->CreateTable(invRow));
		invenLayer->addChild(invTable.at(invRow));
		invTable.at(invRow)->setVisible(false);
	}
	
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
	Vec2 shipPosition = Vec2((winSize.width + 470) / 2 / PTM_RATIO, ((winSize.height / 3) - 60) / PTM_RATIO);
	ship = Sprite::createWithSpriteFrame(ShipFrameCache->getSpriteFrameByName("Ship 0.png"));
	ship->setAnchorPoint(Vec2(0.5, 0.1));
	ship->setPosition((winSize.width + 470) / 2 / PTM_RATIO, ((winSize.height / 3) - 60) / PTM_RATIO);
	ship->setLocalZOrder(2);
	ship->setScale(3.f);
	this->addChild(ship);

	fisherman = Sprite::create("Sprites/Fisherman.png");
	fisherman->setAnchorPoint(Vec2::ZERO);
	fisherman->setPosition(Vec2(-4, 24));
	fisherman->setLocalZOrder(1);
	ship->addChild(fisherman);

	fstUpdate = Sprite::create("Sprites/FishingStat_default.png");
	fstUpdate->setAnchorPoint(Vec2::ZERO);
	fstUpdate->setPosition(Vec2(14, 24));
	fstUpdate->setScale(0.5f);
	fisherman->addChild(fstUpdate);

	//환경 구조물배치----------------------------------------------------------------------------------------

	//메뉴
	btn_inventory = MenuItemImage::create("Sprites/Button_bagclose.png", "Sprites/Button_bagopen.png",
		CC_CALLBACK_1(LSFGame::doPushInventory, this));
	btn_inventory->setScale(1.5f);
	inventoryMenu = Menu::create(btn_inventory, nullptr);
	inventoryMenu->setAnchorPoint(Vec2(0.5, 0.5));
	inventoryMenu->setPosition(Vec2(winSize.width - 140, winSize.height / 5 - 100));
	inventoryMenu->alignItemsHorizontally();
	this->addChild(inventoryMenu, 4);

	btn_modeswitch = MenuItemImage::create("Sprites/Button_modeauto.png", "Sprites/Button_modemanual.png",
		CC_CALLBACK_1(LSFGame::doChangeMode, this));
	modeswitchMenu = Menu::create(btn_modeswitch, nullptr);
	modeswitchMenu->setAnchorPoint(Vec2(0.5, 0.5));
	modeswitchMenu->setPosition(Vec2(winSize.width - 140, winSize.height - 100));
	modeswitchMenu->alignItemsHorizontally();
	this->addChild(modeswitchMenu, 3);

	////애니메이션

	//Ship	Normal(1), Windy(2), Snowy(3), Rainny(4), ThunderStorm(5)
	ShipStat = 2;

	if (ShipStat == 1) {
		if (ship->getNumberOfRunningActions() != 0) {
			ship->cleanup();
		}
		auto shipNormalAnim = animCreate->CreateAnim("Sprites/Ship_normal.json", "Ship", 5, 0.1f);
		auto shipAnimate = Animate::create(shipNormalAnim);
		auto repShip = RepeatForever::create(shipAnimate);
		ship->runAction(repShip);
	}
	else if (ShipStat == 2) {
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

	//Weather effect	Normal(1), Windy(2), Snowy(3), Rainny(4), ThunderStorm(5)
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
void LSFGame::WorldTimer(float dt)
{
	//time concept
	/*
	1 gmin = 2.5sec
	1 ghour = 15sec
	1 gday = 6 min
	*/
	wTime++;
	//log("WORLD TIME : %d", wTime);
	if (wTime == 120)
	{
		dayChanger = 1;
	}
	else if (wTime == 240)
	{
		dayChanger = 2;
	}
	else if (wTime == 360)
	{
		dayChanger = 3;
		wTime = 0;
	}

	//테스트 로그 출력 
	//log("--------------------------------------------------------------WorldTimer: %d", wTime);
	//if (wTime <= 120)
	//{
	//	log("--------------------------------------------------------------Day Change : %d morning", day);
	//	
	//	log("--------------------------------------------------------------wTime Init!!");
	//	if (wTime == 120) { dayChanger = 1; }
	//}
	//else if (wTime > 120 && wTime <= 240)
	//{
	//	
	//	if (wTime == 130)
	//	log("--------------------------------------------------------------Day Change : %d noon", day);
	//	day = 2; //오후
	//	if (wTime == 120) { dayChanger = 2; }
	//}
	//else if (wTime > 240 && wTime <= 360)
	//{
	//	log("--------------------------------------------------------------Day Change : %d night", day);
	//	day = 3; //저녁
	//	if (wTime == 360) { wTime = 0; }
	//	
	//}

}

void LSFGame::dayChangerF(int type)
{

	//Init 
	if (wtInit < 120) {
		backDefault = Sprite::create("Sprites/Game_bg.png");
		backDefault->setAnchorPoint(Vec2::ZERO);
		backDefault->setPosition(Vec2::ZERO);
		backDefault->setOpacity(0);
		this->addChild(backDefault, 0);
		auto backDfFadeIn = FadeIn::create(1.f);
		backDefault->runAction(backDfFadeIn);

		log("dayChange! Morning");
		if (back->getNumberOfRunningActions() != 0) { back->stopAction(repMain); }
		mainAnim = animCreate->CreateAnim("Sprites/Game_cloudcut.json", "Game_cloudcut", 15, 0.2f);
		mainAnimate = Animate::create(mainAnim);
		repMain = RepeatForever::create(mainAnimate);
		back->runAction(repMain);
		wtInit = 999;
	}
	else if (wtInit > 120 && wtInit < 240) {
		backDefault = Sprite::create("Sprites/Game_bg_sn.png");
		backDefault->setAnchorPoint(Vec2::ZERO);
		backDefault->setPosition(Vec2::ZERO);
		backDefault->setOpacity(0);
		this->addChild(backDefault, 0);
		auto backDfFadeIn = FadeIn::create(1.f);
		backDefault->runAction(backDfFadeIn);

		log("dayChange! Noon");
		if (back->getNumberOfRunningActions() != 0) { back->stopAction(repMain); }
		mainAnim = animCreate->CreateAnim("Sprites/Game_cloudcut_sn.json", "Game_cloudcut", 15, 0.2f);
		mainAnimate = Animate::create(mainAnim);
		repMain = RepeatForever::create(mainAnimate);
		back->runAction(repMain);
		wtInit = 999;
	}
	else if (wtInit > 240 && wtInit < 360) {
		backDefault = Sprite::create("Sprites/Game_bg_nt.png");
		backDefault->setAnchorPoint(Vec2::ZERO);
		backDefault->setPosition(Vec2::ZERO);
		backDefault->setOpacity(0);
		this->addChild(backDefault, 0);
		auto backDfFadeIn = FadeIn::create(1.f);
		backDefault->runAction(backDfFadeIn);

		log("dayChange! Night");
		if (back->getNumberOfRunningActions() != 0) { back->stopAction(repMain); }
		mainAnim = animCreate->CreateAnim("Sprites/Game_cloudcut_nt.json", "Game_cloudcut", 15, 0.2f);
		mainAnimate = Animate::create(mainAnim);
		repMain = RepeatForever::create(mainAnimate);
		back->runAction(repMain);
		wtInit = 999;
	}

	//Tick Func
	if (type == 1)
	{
		backDefault = Sprite::create("Sprites/Game_bg.png");
		backDefault->setAnchorPoint(Vec2::ZERO);
		backDefault->setPosition(Vec2::ZERO);
		backDefault->setOpacity(0);
		this->addChild(backDefault, 0);
		auto backDfFadeIn = FadeIn::create(1.f);
		backDefault->runAction(backDfFadeIn);

		log("dayChange! Morning");
		if (back->getNumberOfRunningActions() != 0) { back->stopAction(repMain); back->setOpacity(0); }
		mainAnim = animCreate->CreateAnim("Sprites/Game_cloudcut.json", "Game_cloudcut", 15, 0.2f);
		mainAnimate = Animate::create(mainAnim);
		repMain = RepeatForever::create(mainAnimate);
		back->runAction(repMain);
		auto backFadeIn = FadeIn::create(1.0f);
		back->runAction(backFadeIn);
		dayChanger = 0;
	}
	else if (type == 2)
	{
		backDefault = Sprite::create("Sprites/Game_bg_sn.png");
		backDefault->setAnchorPoint(Vec2::ZERO);
		backDefault->setPosition(Vec2::ZERO);
		backDefault->setOpacity(0);
		this->addChild(backDefault, 0);
		auto backDfFadeIn = FadeIn::create(1.f);
		backDefault->runAction(backDfFadeIn);

		log("dayChange! Noon");
		if (back->getNumberOfRunningActions() != 0) { back->stopAction(repMain); back->setOpacity(0); }
		mainAnim = animCreate->CreateAnim("Sprites/Game_cloudcut_sn.json", "Game_cloudcut", 15, 0.2f);
		mainAnimate = Animate::create(mainAnim);
		repMain = RepeatForever::create(mainAnimate);
		back->runAction(repMain);
		auto backFadeIn = FadeIn::create(1.f);
		back->runAction(backFadeIn);
		dayChanger = 0;
	}
	else if (type == 3)
	{
		backDefault = Sprite::create("Sprites/Game_bg_nt.png");
		backDefault->setAnchorPoint(Vec2::ZERO);
		backDefault->setPosition(Vec2::ZERO);
		backDefault->setOpacity(0);
		this->addChild(backDefault, 0);
		auto backDfFadeIn = FadeIn::create(1.f);
		backDefault->runAction(backDfFadeIn);

		log("dayChange! Night");
		if (back->getNumberOfRunningActions() != 0) { back->stopAction(repMain); back->setOpacity(0); }
		mainAnim = animCreate->CreateAnim("Sprites/Game_cloudcut_nt.json", "Game_cloudcut", 15, 0.2f);
		mainAnimate = Animate::create(mainAnim);
		repMain = RepeatForever::create(mainAnimate);
		back->runAction(repMain);
		auto backFadeIn = FadeIn::create(1.f);
		back->runAction(backFadeIn);
		dayChanger = 0;
	}
}

bool LSFGame::onTouchBegan(Touch* touch, Event* event)
{
	log("Touched! %d", touchCount);
	weatherCount = 1;
	touchPoint = touch->getLocation();
	log("X : %f Y : %f", touchPoint.x, touchPoint.y);
	bool bTouch_craft = craft->getBoundingBox().containsPoint(touchPoint);

	touchRope = touchPoint; // WaterSplash 발생 위치 지정을 위한 변수
	float splashDelay = touchPoint.y;
	prgFailBack->setVisible(false);

	// 게임 화면

	//반자동 모드
	if (modeSwitch != true) {
		if (touchCount == true) {
			if (btnCount == false) {
				if (btnCount == false && fishingStat == false) {
					//낚시 시작 전
					needle = this->addNewSpriteAt(touchPoint, "Sprites/needle.png", 0);
					Vec2 fVec = fisherman->convertToWorldSpace(fisherman->getPosition());

					this->createRope(groundBody, b2Vec2((fVec.x + 16) / PTM_RATIO, (fVec.y - 4) / PTM_RATIO),
						needle, needle->GetLocalCenter(), 1.1f);
					//ropeTouchCount = true;
					log("---------------------------Fishing 1 SA");

					log("---------------------------Fishing 2 SA");
					this->scheduleOnce(schedule_selector(LSFGame::waterSplash), splashDelay / 700);
					log("---------------------------Fishing 3 SA");
					startFishing(1);
					log("---------------------------Fishing 3-1 SA");
				}
				if (hangFish == true) {
					log("---------------------------HangFish true -> Touch SA");
					endFishing(3);
				}
			}
		}
	}
	//수동 모드
	else {
		if (touchCount == true) {
			if (btnCount == false) {
				if (btnCount == false && fishingStat == false) {
					//낚시 시작 전
					manualLayer->setVisible(false);
					needle = this->addNewSpriteAt(touchPoint, "Sprites/needle.png", 0);
					Vec2 fVec = fisherman->convertToWorldSpace(fisherman->getPosition());

					this->createRope(groundBody, b2Vec2((fVec.x + 16) / PTM_RATIO, (fVec.y - 4) / PTM_RATIO),
						needle, needle->GetLocalCenter(), 1.1f);
					//ropeTouchCount = true;
					log("---------------------------Fishing 1 MA");

					log("---------------------------Fishing 2 MA");
					this->scheduleOnce(schedule_selector(LSFGame::waterSplash), splashDelay / 700);
					log("---------------------------Fishing 3 MA");
					startFishing(1);
					log("---------------------------Fishing 3-1 MA");
				}
				if (hangFish == true) {
					log("---------------------------HangFish true -> Touch MA");
					//endFishing(3);
				}
			}
		}
	}

	// 가방이 열려있고 craft가 선택 됐을 때
	if (bTouch_craft && btnCount == true && invOpen->getNumberOfRunningActions() == 0)
	{
		//craftSwitch == true/false On/Off

		//여기에 인벤토리 탭 활성/비활성화 추가 
		if (craftSwitch == true)
		{
			craftUsel->setVisible(true);
			craftSel->setVisible(false);
			btnCraft->setVisible(false);
			craftSwitch = false;
			/*if (craftInit == 1) { temp1->setScale(1.f); }
			else if (craftInit == 2) { temp1->setScale(1.f); temp2->setScale(1.f); }*/
			craftInit = 0;
			if (btnCraft->getChildByName("clone1") != nullptr)
			{
				btnCraft->removeChildByName("clone1");

				if (btnCraft->getChildByName("clone2") != nullptr)
					btnCraft->removeChildByName("clone2");
			}

			//log("craftSwitch Status: Off", craftSwitch);
		}
		else
		{
			craftUsel->setVisible(false);
			craftSel->setVisible(true);
			btnCraft->setVisible(true);
			craftSwitch = true;
			tmpCount = 1;

			//log("craftSwitch Status: On", craftSwitch);
		}
	}

	//Combine 예외 처리
	if (craftSwitch == true && tmpCount >= 0 && tableComplete == true)
	{
		moveCheck == false;
	}

	return true;
}
void LSFGame::onTouchMoved(Touch* touch, Event* event)
{
	//Combine 예외 처리
	if (craftSwitch == true && tmpCount >= 0 && tableComplete == true)
	{
		moveCheck == true;
	}

}
void LSFGame::onTouchEnded(Touch* touch, Event* event)
{
	bool bTouch_combine = btnCraft->getBoundingBox().containsPoint(touchPoint);

	//Combine 함수에 필요한 매개변수 초기화
	if (craftSwitch == true && tmpCount >= 0 && tableComplete == true && moveCheck == false)
	{
		
		std::string cellName;
		log("tmpCount: %d", tmpCount);

		for (int i = 0; i < 8; i++)
		{
			//log("!!!! i: %d", i);
			bTouch_table = invTable.at(i)->getBoundingBox().containsPoint(touchPoint);

			if (bTouch_table == true)
			{
				tableTag = LSFSingleton::getInstance()->tableTag;
				cellIdx = LSFSingleton::getInstance()->cellIdx;
				cellTag = LSFSingleton::getInstance()->cellTag;

				if (cellTag == -1 || cellTag == -2) { continue; }

				log("[TouchEnded] table :%d\ncellIdx :%d\ncellTag :%d", tableTag, cellIdx, cellTag);
				log("bTouch_table True");
				if (tmpCount == 1) {
					log("tmpCount == 1 Activate");
					temp1 = invTable.at(tableTag)->cellAtIndex(cellIdx);
					temp1Tag = cellTag;
					craftTmp1 = ((Sprite*)temp1->getChildByTag(cellTag));
					auto clone1 = Sprite::createWithTexture(craftTmp1->getTexture());
					clone1->setAnchorPoint(Vec2(0.5, 0.5));
					clone1->setPosition(Vec2(60, 60));
					clone1->setName("clone1");
					btnCraft->addChild(clone1, 4);

					craftInit++;
				}
				else if (temp1 == invTable.at(tableTag)->cellAtIndex(cellIdx)) { continue; }
				else if (tmpCount == 0 && temp1 != invTable.at(tableTag)->cellAtIndex(cellIdx))
				{
					log("tmpCount == 0 Activate");
					temp2 = invTable.at(tableTag)->cellAtIndex(cellIdx);
					temp2Tag = cellTag;
					craftTmp2 = ((Sprite*)temp2->getChildByTag(cellTag));
					auto clone2 = Sprite::createWithTexture(craftTmp2->getTexture());
					clone2->setAnchorPoint(Vec2(0.5, 0.5));
					clone2->setPosition(Vec2(240, 60));
					clone2->setName("clone2");
					btnCraft->addChild(clone2, 4);

					craftInit++;
				}

				tmpCount--;
				break;
			}
		}
	}
	// Combine 함수 실행 및 Sprite 초기화 
	if (btnCount == true && craftSwitch == true && bTouch_combine == true && tableComplete == true)
	{
		if (tmpCount < 0) {
			log("bTouch_combine\ntemp1Tag :%d\ttemp2Tag :%d", temp1Tag, temp2Tag);
			if ((temp1Tag != -1 && temp2Tag != -1) || (temp1Tag != -2 && temp2Tag != -2))
			{
				combine(temp1Tag, temp2Tag, temp1, temp2);
			}
		}
		else if (tmpCount >= 0) 
		{
			tableTag = 0;
			cellIdx = 0;
			cellTag = 0;
			
			if (btnCraft->getChildByName("clone1") != nullptr)
			{
				btnCraft->removeChildByName("clone1");

				if (btnCraft->getChildByName("clone2") != nullptr)
					btnCraft->removeChildByName("clone2");
			}
			tmpCount = 1;
		}

	}

}

void LSFGame::combine(int itemA, int itemB, TableViewCell* cellA, TableViewCell* cellB)
{

	log("combine in itemA : %d itemB : %d", itemA, itemB);
	log("combine in cellA : %d cellB : %d", cellA, cellB);

	//애니메이션
	auto combineAnim = animCreate->CreateAnim("Sprites/Button_combine2.json", "Button_combine2", 8, 0.1f);
	auto combineAnimate = Animate::create(combineAnim);
	auto repCombine = Repeat::create(combineAnimate, 1);
	btnCraft->setAnchorPoint(Vec2::ZERO);
	btnCraft->setPosition(Vec2(198, 340));
	btnCraft->runAction(repCombine);

	//조합 기능
	//인벤토리 공백
	Vec2 cAvec = cellA->getPosition();
	Vec2 cBvec = cellB->getPosition();
	Vec2 cellAncher = Vec2(0.5, 0.5);
	log("cAvec x : %f\tcAvec y : %f", cAvec.x, cAvec.y);
	log("cBvec x : %f\tcBvec y : %f", cBvec.x, cBvec.y);

	cellA->removeAllChildren();
	cellB->removeAllChildren();
	cellA->addChild(Sprite::createWithTexture(invNull->getTexture()));
	cellA->setTag(-2);
	//cellA->setPosition(cAvec);
	//cellA->setAnchorPoint(cellAncher);
	cellB->addChild(Sprite::createWithTexture(invNull->getTexture()));
	cellB->setTag(-2);
	//cellB->setPosition(cBvec);
	//cellB->setAnchorPoint(cellAncher);
	items(2);

	if (btnCraft->getChildByName("clone1") != nullptr)
	{
		btnCraft->removeChildByName("clone1");

		if (btnCraft->getChildByName("clone2") != nullptr)
			btnCraft->removeChildByName("clone2");
	}
	tmpCount = 1;
}

void LSFGame::doPushInventory(Ref * pSender) {
	if (btnCount == false) {
		invenLayer->setVisible(true);

		//invOpen Animation
		craftUsel->setVisible(false);
		invenAnim = animCreate->CreateAnim("Sprites/inventory_open.json", "inventory_open", 9, 0.2f);
		invenAnimate = Animate::create(invenAnim);
		repInven = Repeat::create(invenAnimate, 1);
		invOpen->runAction(repInven);

		//craft->setVisible(true);
		btn_inventory->selected();
		btnCount = true;
		craftSwitch == false;

		modeswitchMenu->setEnabled(false);
	}
	else {
		invenLayer->setVisible(false);
		invTab->setVisible(false);
		if (invOpen->getNumberOfRunningActions() != 0) {
			invOpen->stopAllActions();
		}
		//inventory->setVisible(false);
		//craft->setVisible(false);
		btn_inventory->unselected();
		btnCount = false;
		craftSwitch == false;
		cbtnCount = 0;
		craftUsel->setVisible(true);
		craftSel->setVisible(false);
		btnCraft->setVisible(false);
		modeswitchMenu->setEnabled(true);
		invOpenCount = false;
		//인벤토리 비활성화
		for (int invRow = 0; invRow < 24; invRow++)
		{
			invTable.at(invRow)->setVisible(false);
		}
	}
}

void LSFGame::doPushInvTab(Ref * pSender) {
	MenuItemImage* pMenuItem = (MenuItemImage *)(pSender);
	int tag = (int)pMenuItem->getTag();
	log("MenuItem tag :%d", tag);
	
	if (tag == 10)
	{
		inv1->selected();
		inv2->unselected();
		inv3->unselected();
		for (int invRow = 0; invRow < 8; invRow++)
		{
			invTable.at(invRow)->setVisible(true);
		}
		for (int invRow = 8; invRow < 16; invRow++)
		{
			invTable.at(invRow)->setVisible(false);
		}
		for (int invRow = 16; invRow < 25; invRow++)
		{
			invTable.at(invRow)->setVisible(false);
		}
		lastSel = 1;
	}
	else if (tag == 20)
	{
		inv1->unselected();
		inv2->selected();
		inv3->unselected();

		for (int invRow = 0; invRow < 8; invRow++)
		{
			invTable.at(invRow)->setVisible(false);
		}

		for (int invRow = 8; invRow < 16; invRow++)
		{
			invTable.at(invRow)->setVisible(true);
		}
		for (int invRow = 16; invRow < 25; invRow++)
		{
			invTable.at(invRow)->setVisible(false);
		}
		lastSel = 2;
	}
	else if (tag == 30)
	{
		inv1->unselected();
		inv2->unselected();
		inv3->selected();

		for (int invRow = 0; invRow < 8; invRow++)
		{
			invTable.at(invRow)->setVisible(false);
		}

		for (int invRow = 8; invRow < 16; invRow++)
		{
			invTable.at(invRow)->setVisible(false);
		}
		for (int invRow = 16; invRow < 25; invRow++)
		{
			invTable.at(invRow)->setVisible(true);
		}
		lastSel = 3;
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
	groundEdge.Set(b2Vec2(0, 3.5f), b2Vec2(winSize.width / PTM_RATIO, 3.5f));
	groundBody->CreateFixture(&boxShapeDef);
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
	bottomBodyDef.position.Set(winSize.width / 2 / PTM_RATIO, 1.2f);
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
	rightBodyDef.position.Set((winSize.width) / PTM_RATIO, 0);
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
	flowBody0 = this->addNewSpriteFlow(Vec2((winSize.width / 2), winSize.height / 3 - 100), Size(100, 5), b2_dynamicBody, flowRand, 0);
	flowBody1 = this->addNewSpriteFlow(Vec2((winSize.width / 2) - 40, winSize.height / 3 - 120), Size(10, 10), b2_dynamicBody, 0, 0);
	flowBody2 = this->addNewSpriteFlow(Vec2((winSize.width / 2) + 40, winSize.height / 3 - 120), Size(10, 10), b2_dynamicBody, 0, 0);

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
	flowBody3 = this->addNewSpriteFlow(Vec2((winSize.width / 2), winSize.height / 3 - 160), Size(100, 10), b2_dynamicBody, flowRand, 0);
	flowBody4 = this->addNewSpriteFlow(Vec2((winSize.width / 2) - 40, winSize.height / 3 - 180), Size(20, 20), b2_dynamicBody, 0, 0);
	flowBody5 = this->addNewSpriteFlow(Vec2((winSize.width / 2) + 40, winSize.height / 3 - 180), Size(20, 20), b2_dynamicBody, 0, 0);

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
	flowBody6 = this->addNewSpriteFlow(Vec2((winSize.width / 2), winSize.height / 3 - 220), Size(100, 15), b2_dynamicBody, flowRand, 0);
	flowBody7 = this->addNewSpriteFlow(Vec2((winSize.width / 2) - 40, winSize.height / 3 - 240), Size(20, 20), b2_dynamicBody, 0, 0);
	flowBody8 = this->addNewSpriteFlow(Vec2((winSize.width / 2) + 40, winSize.height / 3 - 240), Size(20, 20), b2_dynamicBody, 0, 0);

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
	this->addChild(ropeSpriteSheet, 2);

	//배
	b2BodyDef shipBodyDef;
	shipBodyDef.type = b2_dynamicBody;
	shipBodyDef.position.Set((winSize.width + 470) / 2 / PTM_RATIO, ((winSize.height / 3)) / PTM_RATIO);
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

	//수표면
	b2BodyDef waterBodyDef;
	waterBodyDef.type = b2_kinematicBody;
	waterBodyDef.position.Set((winSize.width) / 2 / PTM_RATIO, ((winSize.height / 3) - 80) / PTM_RATIO);
	waterBodyDef.linearVelocity = b2Vec2(-1.0f, 0);

	b2Body* waterBody = _world->CreateBody(&waterBodyDef);
	b2CircleShape kinematicCircle;
	kinematicCircle.m_radius = 0.05;

	b2FixtureDef waterfixtureDef;
	waterfixtureDef.shape = &kinematicCircle;
	waterfixtureDef.density = 1.0f;
	waterfixtureDef.filter.groupIndex = -1;
	waterBody->CreateFixture(&waterfixtureDef);

	b2BodyDef waterBodyDef2;
	waterBodyDef2.type = b2_kinematicBody;
	waterBodyDef2.position.Set((winSize.width) / 2 / PTM_RATIO, ((winSize.height / 3) - 80) / PTM_RATIO);
	waterBodyDef2.linearVelocity = b2Vec2(1.0f, 0);

	b2Body* waterBody2 = _world->CreateBody(&waterBodyDef2);
	b2FixtureDef waterfixtureDef2;
	waterfixtureDef2.shape = &kinematicCircle;
	waterfixtureDef2.density = 1.0f;
	waterfixtureDef2.filter.groupIndex = -1;
	waterBody2->CreateFixture(&waterfixtureDef2);

	return true;
}
b2Body* LSFGame::addNewSpriteAt(Vec2 point, const std::string & imagepath, int tag)
{
	b2CircleShape spriteShape;
	//Get the sprite frome the sprite sheet
	addFish = Sprite::create(imagepath);
	addFish->setAnchorPoint(Vec2(0.5, 0.8));

	if (tag == 0) {

		addFish->setTag(99);
		this->addChild(addFish, 2);

		//Defines the body of sprite
		needlebodyDef.type = b2_dynamicBody;
		needlebodyDef.position = b2Vec2(point.x / PTM_RATIO, point.y / PTM_RATIO);
		needlebodyDef.userData = addFish;
		needlebodyDef.linearDamping = 0.3f;

		needleBody = _world->CreateBody(&needlebodyDef);

		spriteShape.m_radius = 0.1;
		needlefixtureDef.shape = &spriteShape;
		needlefixtureDef.density = 1.0f;
		needlefixtureDef.friction = 0.2f;
		needlefixtureDef.restitution = 0.4f;
		needlefixtureDef.filter.categoryBits = 0x01;
		needlefixtureDef.filter.maskBits = 0x03;
		needlefixtureDef.filter.groupIndex = -1;


		needleBody->CreateFixture(&needlefixtureDef);
		needleBody->SetFixedRotation(true);
		return needleBody;
	}
	else if (resultCount == true)
	{

		addFish->setTag(tag);
		this->addChild(addFish, 2);
		if (addFish->getTag() == tag)
		{
			addFish->setVisible(false);
		}
		needleBody->SetUserData(addFish);
		resultCount = false;
	}
	else if (resultCount == false)
	{
		addFish->setTag(tag);
		this->addChild(addFish, 2);

		needleBody->SetUserData(addFish);
		resultCount = true;
	}
}
b2Body* LSFGame::addNewSpriteFlow(Vec2 point, Size size, b2BodyType bodytype, int flowtype, int type)
{
	b2BodyDef bodyDef;
	bodyDef.type = bodytype;
	bodyDef.position.Set(point.x / PTM_RATIO, point.y / PTM_RATIO);

	if (flowtype) {
		if (flowtype == 1) {
			auto flowSprite = Sprite::createWithTexture(texture = Director::getInstance()->getTextureCache()->addImage("Sprites/Items/Fishes/Fish007.png"),
				Rect(0, 0, 24, 16));
			flow.pushBack(flowSprite);
			flow.at(flowCount)->setPosition(point);
			flow.at(flowCount)->setTag(flowCount);
			this->addChild(flow.at(flowCount), 3);
			flow.at(flowCount)->setFlippedX(true);
			bodyDef.userData = flow.at(flowCount);
			flowCount++;
		}
		else if (flowtype == 2) {
			auto flowSprite = Sprite::createWithTexture(texture = Director::getInstance()->getTextureCache()->addImage("Sprites/Items/Fishes/Fish013.png"),
				Rect(0, 0, 34, 34));
			flow.pushBack(flowSprite);
			flow.at(flowCount)->setPosition(point);
			flow.at(flowCount)->setTag(flowCount);
			this->addChild(flow.at(flowCount), 3);
			flow.at(flowCount)->setFlippedX(true);
			bodyDef.userData = flow.at(flowCount);
			flowCount++;
		}
		else if (flowtype == 3) {
			auto flowSprite = Sprite::createWithTexture(texture = Director::getInstance()->getTextureCache()->addImage("Sprites/Items/Fishes/Fish018.png"),
				Rect(0, 0, 34, 34));
			flow.pushBack(flowSprite);
			flow.at(flowCount)->setPosition(point);
			flow.at(flowCount)->setTag(flowCount);
			this->addChild(flow.at(flowCount), 3);
			flow.at(flowCount)->setFlippedX(true);
			bodyDef.userData = flow.at(flowCount);
			flowCount++;
		}
		else if (flowtype == 4) {
			auto flowSprite = Sprite::createWithTexture(texture = Director::getInstance()->getTextureCache()->addImage("Sprites/Items/Fishes/Fish004.png"),
				Rect(0, 0, 34, 34));
			flow.pushBack(flowSprite);
			flow.at(flowCount)->setPosition(point);
			flow.at(flowCount)->setTag(flowCount);
			this->addChild(flow.at(flowCount), 3);
			flow.at(flowCount)->setFlippedX(true);
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

//인벤토리 정렬 함수 정의 필요
void LSFGame::items(int tag) {
	log("items");
	if (kindof == 1) {
		if (tag == 1) {
			log("Fishing Success & get Item");
			for (int table = 0; table < 8;)
			{
				log("items for table : %d", table);
				for (int cell = 0; cell < 10;)
				{
					log("items for cell : %d", cell);
					if (invTable.at(table)->cellAtIndex(cell)->getTag() == -1 || invTable.at(table)->cellAtIndex(cell)->getTag() == -2) {
						auto invSprite = Sprite::create(itemName.c_str());
						invSprite->setTag((rarity * 1000 + chance));
						int tmpTag = invTable.at(table)->cellAtIndex(cell)->getTag();
						invPosition = invTable.at(table)->cellAtIndex(cell)->getPosition();
						invTable.at(table)->cellAtIndex(cell)->removeAllChildren();
						invTable.at(table)->cellAtIndex(cell)->addChild(invSprite, 4);
						invTable.at(table)->cellAtIndex(cell)->setTag((rarity * 1000 + chance));

						if (tmpTag == -1)
						{
							invTable.at(table)->cellAtIndex(cell)->setPosition(Vec2(invPosition.x + 20, invPosition.y + 20));
						}
						else
						{
							invTable.at(table)->cellAtIndex(cell)->setPosition(Vec2(invPosition.x, invPosition.y));
						}
						log("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!x : %f\ty : %f", invPosition.x + 20, invPosition.y + 20);
						invTable.at(table)->cellAtIndex(cell)->setAnchorPoint(Vec2(0.5, 0.5));
						log("invTable/Cell Tag : %d, %d", invTable.at(table)->getTag(), invTable.at(table)->cellAtIndex(cell)->getTag());
						return;
					}
					else {
						cell++;
					}
				}
				table++;
			}
		}
		else if (tag == 2)
		{
			log("Item Combine & Sort");
			for (int table = 8; table < 16;)
			{
				log("items for table : %d", table);
				for (int cell = 0; cell < 10;)
				{
					log("items for cell : %d", cell);
					if (invTable.at(table)->cellAtIndex(cell)->getTag() == -1 || invTable.at(table)->cellAtIndex(cell)->getTag() == -2) {
						auto invSprite = Sprite::create("Sprites/Items/Consume/Consume007.png");
						invSprite->setTag(9999);
						int tmpTag = invTable.at(table)->cellAtIndex(cell)->getTag();
						invPosition = invTable.at(table)->cellAtIndex(cell)->getPosition();
						invTable.at(table)->cellAtIndex(cell)->removeAllChildren();
						invTable.at(table)->cellAtIndex(cell)->addChild(invSprite, 4);
						invTable.at(table)->cellAtIndex(cell)->setTag(9999);

						if (tmpTag == -1)
						{
							invTable.at(table)->cellAtIndex(cell)->setPosition(Vec2(invPosition.x + 20, invPosition.y + 20));
						}
						else
						{
							invTable.at(table)->cellAtIndex(cell)->setPosition(Vec2(invPosition.x, invPosition.y));
						}
						log("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!x : %f\ty : %f", invPosition.x + 20, invPosition.y + 20);
						invTable.at(table)->cellAtIndex(cell)->setAnchorPoint(Vec2(0.5, 0.5));
						log("invTable/Cell Tag : %d, %d", invTable.at(table)->getTag(), invTable.at(table)->cellAtIndex(cell)->getTag());
						return;
					}
					else {
						cell++;
					}
				}
				table++;
			}
		}
	}
	else if (kindof == 2) {
		if (tag == 1) {
			log("Fishing Success & get Item");
			for (int table = 8; table < 16;)
			{
				log("items for table : %d", table);
				for (int cell = 0; cell < 10;)
				{
					log("items for cell : %d", cell);
					if (invTable.at(table)->cellAtIndex(cell)->getTag() == -1 || invTable.at(table)->cellAtIndex(cell)->getTag() == -2) {
						auto invSprite = Sprite::create(itemName.c_str());
						invSprite->setTag((rarity * 1000 + chance));
						int tmpTag = invTable.at(table)->cellAtIndex(cell)->getTag();
						invPosition = invTable.at(table)->cellAtIndex(cell)->getPosition();
						invTable.at(table)->cellAtIndex(cell)->removeAllChildren();
						invTable.at(table)->cellAtIndex(cell)->addChild(invSprite, 4);
						invTable.at(table)->cellAtIndex(cell)->setTag((rarity * 1000 + chance));

						if (tmpTag == -1)
						{
							invTable.at(table)->cellAtIndex(cell)->setPosition(Vec2(invPosition.x + 20, invPosition.y + 20));
						}
						else
						{
							invTable.at(table)->cellAtIndex(cell)->setPosition(Vec2(invPosition.x, invPosition.y));
						}
						log("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!x : %f\ty : %f", invPosition.x + 20, invPosition.y + 20);
						invTable.at(table)->cellAtIndex(cell)->setAnchorPoint(Vec2(0.5, 0.5));
						log("invTable/Cell Tag : %d, %d", invTable.at(table)->getTag(), invTable.at(table)->cellAtIndex(cell)->getTag());
						return;
					}
					else {
						cell++;
					}
				}
				table++;
			}
		}
		else if (tag == 2)
		{
			log("Item Combine & Sort");
			for (int table = 8; table < 16;)
			{
				log("items for table : %d", table);
				for (int cell = 0; cell < 10;)
				{
					log("items for cell : %d", cell);
					if (invTable.at(table)->cellAtIndex(cell)->getTag() == -1 || invTable.at(table)->cellAtIndex(cell)->getTag() == -2) {
						auto invSprite = Sprite::create("Sprites/Items/Consume/Consume007.png");
						invSprite->setTag(9999);
						int tmpTag = invTable.at(table)->cellAtIndex(cell)->getTag();
						invPosition = invTable.at(table)->cellAtIndex(cell)->getPosition();
						invTable.at(table)->cellAtIndex(cell)->removeAllChildren();
						invTable.at(table)->cellAtIndex(cell)->addChild(invSprite, 4);
						invTable.at(table)->cellAtIndex(cell)->setTag(9999);

						if (tmpTag == -1)
						{
							invTable.at(table)->cellAtIndex(cell)->setPosition(Vec2(invPosition.x + 20, invPosition.y + 20));
						}
						else
						{
							invTable.at(table)->cellAtIndex(cell)->setPosition(Vec2(invPosition.x, invPosition.y));
						}
						log("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!x : %f\ty : %f", invPosition.x + 20, invPosition.y + 20);
						invTable.at(table)->cellAtIndex(cell)->setAnchorPoint(Vec2(0.5, 0.5));
						log("invTable/Cell Tag : %d, %d", invTable.at(table)->getTag(), invTable.at(table)->cellAtIndex(cell)->getTag());
						return;
					}
					else {
						cell++;
					}
				}
				table++;
			}
		}
	}
	else if (kindof == 3) {
		if (tag == 1) {
			log("Fishing Success & get Item");
			for (int table = 16; table < 25;)
			{
				log("items for table : %d", table);
				for (int cell = 0; cell < 10;)
				{
					log("items for cell : %d", cell);
					if (invTable.at(table)->cellAtIndex(cell)->getTag() == -1 || invTable.at(table)->cellAtIndex(cell)->getTag() == -2) {
						auto invSprite = Sprite::create(itemName.c_str());
						invSprite->setTag((rarity * 1000 + chance));
						int tmpTag = invTable.at(table)->cellAtIndex(cell)->getTag();
						invPosition = invTable.at(table)->cellAtIndex(cell)->getPosition();
						invTable.at(table)->cellAtIndex(cell)->removeAllChildren();
						invTable.at(table)->cellAtIndex(cell)->addChild(invSprite, 4);
						invTable.at(table)->cellAtIndex(cell)->setTag((rarity * 1000 + chance));

						if (tmpTag == -1)
						{
							invTable.at(table)->cellAtIndex(cell)->setPosition(Vec2(invPosition.x + 20, invPosition.y + 20));
						}
						else
						{
							invTable.at(table)->cellAtIndex(cell)->setPosition(Vec2(invPosition.x, invPosition.y));
						}
						log("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!x : %f\ty : %f", invPosition.x + 20, invPosition.y + 20);
						invTable.at(table)->cellAtIndex(cell)->setAnchorPoint(Vec2(0.5, 0.5));
						log("invTable/Cell Tag : %d, %d", invTable.at(table)->getTag(), invTable.at(table)->cellAtIndex(cell)->getTag());
						return;
					}
					else {
						cell++;
					}
				}
				table++;
			}
		}
		else if (tag == 2)
		{
			log("Item Combine & Sort");
			for (int table = 8; table < 16;)
			{
				log("items for table : %d", table);
				for (int cell = 0; cell < 10;)
				{
					log("items for cell : %d", cell);
					if (invTable.at(table)->cellAtIndex(cell)->getTag() == -1 || invTable.at(table)->cellAtIndex(cell)->getTag() == -2) {
						auto invSprite = Sprite::create("Sprites/Items/Consume/Consume007.png");
						invSprite->setTag(9999);
						int tmpTag = invTable.at(table)->cellAtIndex(cell)->getTag();
						invPosition = invTable.at(table)->cellAtIndex(cell)->getPosition();
						invTable.at(table)->cellAtIndex(cell)->removeAllChildren();
						invTable.at(table)->cellAtIndex(cell)->addChild(invSprite, 4);
						invTable.at(table)->cellAtIndex(cell)->setTag(9999);

						if (tmpTag == -1)
						{
							invTable.at(table)->cellAtIndex(cell)->setPosition(Vec2(invPosition.x + 20, invPosition.y + 20));
						}
						else
						{
							invTable.at(table)->cellAtIndex(cell)->setPosition(Vec2(invPosition.x, invPosition.y));
						}
						log("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!x : %f\ty : %f", invPosition.x + 20, invPosition.y + 20);
						invTable.at(table)->cellAtIndex(cell)->setAnchorPoint(Vec2(0.5, 0.5));
						log("invTable/Cell Tag : %d, %d", invTable.at(table)->getTag(), invTable.at(table)->cellAtIndex(cell)->getTag());
						return;
					}
					else {
						cell++;
					}
				}
				table++;
			}
		}
	}
}


std::string LSFGame::itemCreate(int day, int weather)
{
	//Day - init(0), morning(1), noon(2), night(3)
	//Weather - Normal(1), Windy(2), Snowy(3), Rainny(4), ThunderStorm(5)
	//chance = random(0,89) + (day * weather * 2)
	//rarity - Nomal(01~9), Magic(10~19), Rare(100~109), Unique(110~119)

	chance = random(0, 87) + (day * weather * 2);
	char itemFullpath[100];

	log("ItemCreate Activate!\nChance :%d", chance);
	if (chance < 10)
	{
		if (chance == 0) { chance = 1; }
		const std::string imagePath = "Sprites/Items/Fishes/Fish";
		sprintf(itemFullpath, "%s00%d.png", imagePath.c_str(), chance);
		rarity = 1;
		kindof = 3;
	}
	else if (chance >= 10 && chance <= 29)
	{
		const std::string imagePath = "Sprites/Items/Fishes/Fish";
		sprintf(itemFullpath, "%s0%d.png", imagePath.c_str(), chance);
		rarity = 1;
		kindof = 3;
	}
	else if (chance >29 && chance <= 38)
	{
		const std::string imagePath = "Sprites/Items/Consume/Consume";
		sprintf(itemFullpath, "%s00%d.png", imagePath.c_str(), chance - 29);
		rarity = 1;
		kindof = 2;
	}
	else if (chance == 39)
	{
		const std::string imagePath = "Sprites/Items/Equip/Pole";
		sprintf(itemFullpath, "%s00%d.png", imagePath.c_str(), 1);
		rarity = 3;
		kindof = 1;
	}
	else if (chance >= 40 && chance <= 52)
	{
		const std::string imagePath = "Sprites/Items/Fishes/Fish";
		sprintf(itemFullpath, "%s0%d.png", imagePath.c_str(), chance);
		rarity = 2;
		kindof = 3;
	}
	else if (chance > 52 && chance <= 61)
	{
		const std::string imagePath = "Sprites/Items/Consume/Consume";
		sprintf(itemFullpath, "%s0%d.png", imagePath.c_str(), chance - 43);
		rarity = 2;
		kindof = 2;
	}
	else if (chance > 61 && chance <= 79)
	{
		const std::string imagePath = "Sprites/Items/Fishes/Fish";
		sprintf(itemFullpath, "%s0%d.png", imagePath.c_str(), chance);
		rarity = 3;
		kindof = 3;
	}
	else if (chance > 79 && chance <= 87)
	{
		const std::string imagePath = "Sprites/Items/Consume/Consume";
		sprintf(itemFullpath, "%s0%d.png", imagePath.c_str(), chance - 61);
		rarity = 3;
		kindof = 2;
	}
	else if (chance > 87 && chance <= 90)
	{
		const std::string imagePath = "Sprites/Items/Equip/Pole";
		sprintf(itemFullpath, "%s00%d.png", imagePath.c_str(), chance - 86);
		rarity = 4;
		kindof = 1;
	}
	else if (chance > 90 && chance <= 99)
	{
		const std::string imagePath = "Sprites/Items/Fishes/Fish";
		sprintf(itemFullpath, "%s0%d.png", imagePath.c_str(), chance);
		rarity = 3;
		kindof = 3;
	}
	else if (chance > 99 && chance <= 108)
	{
		const std::string imagePath = "Sprites/Items/Fishes/Fish";
		sprintf(itemFullpath, "%s%d.png", imagePath.c_str(), chance);
		rarity = 4;
		kindof = 3;
	}
	else if (chance > 108 && chance <= 112)
	{
		const std::string imagePath = "Sprites/Items/Equip/Pole";
		sprintf(itemFullpath, "%s00%d.png", imagePath.c_str(), chance - 103);
		rarity = 5;
		kindof = 1;
	}
	else if (chance > 112 && chance <= 117)
	{
		const std::string imagePath = "Sprites/Items/Etc/Etc";
		sprintf(itemFullpath, "%s00%d.png", imagePath.c_str(), chance - 112);
		rarity = 0;
		kindof = 3;
	}

	return itemFullpath;
}


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
		jd.maxLength = ropeLength;
		ropeJoint = (b2RopeJoint*)_world->CreateJoint(&jd);

		newRope = new VRope(ropeJoint, ropeSpriteSheet);
		ropes->push_back(newRope);

		return;
	}
	else if (ropeLength < 1 || ropeLength>5) {
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
void LSFGame::ropeRemove(int type) {
	if (prgHangBack->getNumberOfRunningActions() != 0)
	{
		log("rope Remove - > prgLayerBack ");
		prgHangBack->stopAction(seqRepPrgHang);
		prgHangBack->setVisible(false);
	}
	log("---------------------------Fishing 7");
	modeswitchMenu->setEnabled(true);
	if (type == 1) {

		log("---------------------------Fishing 7-1");
		fstChange(4);
		log("Fishing fail!");
		log("TIME OVER");
		joystick->fishingGauge = 0;
		log("EndFishing Gauge Check: %d", joystick->fishingGauge);
	}
	else if (type == 2) {
		log("---------------------------Fishing 7-2");
		fstChange(4);
		log("Fishing fail!");
		log("ropeHealth ZERO");
		this->unschedule(schedule_selector(LSFGame::timerFishing));
		joystick->fishingGauge = 0;
		log("EndFishing Gauge Check: %d", joystick->fishingGauge);
	}
	else if (type == 3) {
		log("---------------------------Fishing 7-3");
		this->unschedule(schedule_selector(LSFGame::timerFishing));
		fstChange(3);
		log("Fishing Success");
		joystick->fishingGauge = 0;
		log("EndFishing Gauge Check: %d", joystick->fishingGauge);
		items(1);
	}

	ropeHealth = 500;
	ropes->clear();

	_world->DestroyJoint(ropeJoint);

	this->unschedule(schedule_selector(LSFGame::ropeTick));
	newRope->removeSprites();
	needle->DestroyFixture(needle->GetFixtureList());
	log("addFish : %d", addFish->getTag());

	removeChildByTag(99);
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

void LSFGame::tick(float dt) {
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

		if (b->GetType() == b2_kinematicBody)
		{
			b2Vec2 v = b->GetPosition();
			if (v.x*PTM_RATIO > winSize.width) {
				b->SetLinearVelocity(b2Vec2(-1.0f, 0));
			}
			else if (v.x < 0) {
				b->SetLinearVelocity(b2Vec2(1.0f, 0));
			}
		}
	}
	//RUT(Rope Update Timer)
	if (ropeTickCount == false) {
		//this->schedule(schedule_selector(LSFGame::ropeTick), 0.095);
		this->schedule(schedule_selector(LSFGame::ropeTick));
		ropeTickCount = true;
	}

	//DayChange
	dayChangerF(dayChanger);

	//(Fish flow Start)---------------------------------------
	//log("flowbody %f", flowBody0->GetPosition().x);
	if (flowBody0->GetPosition().x <= 0.6)
	{
		m_spring1->SetMotorSpeed(-30.0f);
		m_spring2->SetMotorSpeed(-30.0f);
		flow.at(0)->setFlippedX(false);

	}
	else if (flowBody0->GetPosition().x >= 6.6) {
		m_spring1->SetMotorSpeed(30.0f);
		m_spring2->SetMotorSpeed(30.0f);
		flow.at(0)->setFlippedX(true);
	}

	if (flowBody3->GetPosition().x <= 0.6)
	{
		m_spring3->SetMotorSpeed(-25.0f);
		m_spring4->SetMotorSpeed(-25.0f);
		flow.at(1)->setFlippedX(false);
	}
	else if (flowBody3->GetPosition().x >= 6.6) {
		m_spring3->SetMotorSpeed(25.0f);
		m_spring4->SetMotorSpeed(25.0f);
		flow.at(1)->setFlippedX(true);
	}

	if (flowBody6->GetPosition().x <= 0.6)
	{
		m_spring5->SetMotorSpeed(-20.0f);
		m_spring6->SetMotorSpeed(-20.0f);
		flow.at(2)->setFlippedX(false);
	}
	else if (flowBody6->GetPosition().x >= 6.6) {
		m_spring5->SetMotorSpeed(20.0f);
		m_spring6->SetMotorSpeed(20.0f);
		flow.at(2)->setFlippedX(true);
	}

	if (flowBody9->GetPosition().x <= 0.6)
	{
		m_spring7->SetMotorSpeed(-20.0f);
		m_spring8->SetMotorSpeed(-20.0f);
		flow.at(3)->setFlippedX(false);
	}
	else if (flowBody9->GetPosition().x >= 6.6) {
		m_spring7->SetMotorSpeed(20.0f);
		m_spring8->SetMotorSpeed(20.0f);
		flow.at(3)->setFlippedX(true);
	}
	//(Fish flow End)-----------------------------------------

	//RHC(Rope Health Counter Start)-----------------------------
	if (ropeHealth == 0) {
		endFishing(2);
	}
	//RHC(Rope Health Counter End)-------------------------------

	if (joystick->fishingGauge >= 200) { endFishing(3); }

	//invOpen Animation
	if (btnCount == true && invOpenCount == false) {
		if (invOpen->getNumberOfRunningActions() == 0) {
			invTab->setVisible(true);
			craftUsel->setVisible(true);
			invOpenCount = true;
			//인벤토리 활성화
			if (lastSel == 0 || lastSel == 1) {
				for (int invRow = 0; invRow < 8; invRow++)
				{
					invTable.at(invRow)->setVisible(true);
				}
			}
			else if (lastSel == 2) {
				for (int invRow = 8; invRow < 16; invRow++)
				{
					invTable.at(invRow)->setVisible(true);
				}
			}
			else if (lastSel == 3) {
				for (int invRow = 16; invRow < 25; invRow++)
				{
					invTable.at(invRow)->setVisible(true);
				}
			}
			
		}
	}
}
void LSFGame::touchCounter(float dt)
{
	if (touchCount == false) {
		touchCount = true;
		joystick->setVisible(false);

	}
	else if (touchCount == true) {
		touchCount = false;
	}
}
void LSFGame::startFishing(float dt)
{
	modeswitchMenu->setEnabled(false);

	log("---------------------------Fishing 4");
	fishingStat = true;
	log("ropeLength: %f", ropeLength);
	if (ropeLength >= 6)
	{
		log("1111-1");
		randomTime = random(10, 20);
		log("1111-2 random : %d", randomTime);
		catchTime = random(7, randomTime - 3);
		log("1111-3");
		ropeHealth = ropeHealth * 12;
		log("1111-4");
	}
	else if (ropeLength > 4 && ropeLength < 6)
	{
		log("2222-1");
		randomTime = random(8, 15);
		log("2222-2 random : %d", randomTime);
		catchTime = random(4, randomTime - 3);
		log("2222-3");
		ropeHealth = ropeHealth * 10;
		log("2222-4");
	}
	else if (ropeLength >= 3 && ropeLength <= 4)
	{
		log("3333-1");
		randomTime = random(5, 10);
		log("3333-2 random : %d", randomTime);
		catchTime = random(2, randomTime - 3);
		log("3333-3");
		ropeHealth = ropeHealth * 5;
		log("3333-4");
	}
	else if (ropeLength >= 0 && ropeLength < 3)
	{
		log("4444-1");
		randomTime = random(5, 10);
		log("4444-2 random : %d", randomTime);
		catchTime = random(2, randomTime - 3);
		log("4444-3");
		ropeHealth = ropeHealth * 5;
		log("4444-4");
	}
	fstChange(1);
	timer = randomTime;
	this->schedule(schedule_selector(LSFGame::timerFishing), 1.f);
	log("---------------------------Fishing 4-END");
}
void LSFGame::timerFishing(float dt) {
	log("timerFishing: %d", timer);
	log("catchTime: %d", catchTime);
	if (--timer == 0) {
		log("timer = 0");
		endFishing(1);
	}
	if (timer != 0) {
		if (catchTime-- == 0) {
			log("Enable catch Fish !!!");
			hangFish = true;
			fstChange(2);
			if (modeSwitch == true) {
				listener->setSwallowTouches(false);
				joystick->setVisible(true);
				manualLayer->setVisible(true);
			}
		}
		if (catchTime < -5) {
			log("Disable catch Fish !!!");
			endFishing(1);
			hangFish = false;
		}

	}
	log("---------------------------Fishing 5");
}
void LSFGame::endFishing(float dt)
{

	log("EndFishing");
	if (modeSwitch == true) {
		listener->setSwallowTouches(true);
	}
	this->unschedule(schedule_selector(LSFGame::timerFishing));
	log("---------------------------Fishing 6");
	ropeRemove(dt);
	joystick->doJoyAnimate(2);
}
void LSFGame::fstChange(int type)
{
	//FishingStat
	if (fstUpdate->getNumberOfRunningActions() != 0) {
		fstUpdate->stopAllActions();
	}

	if (type == 1) {
		auto fstNormalAnim = animCreate->CreateAnim("Sprites/FishingStat_normal.json", "FishingStat", 4, 0.1f);
		auto fstNormalAnimate = Animate::create(fstNormalAnim);
		repFstNormal = RepeatForever::create(fstNormalAnimate);
		fstUpdate->runAction(repFstNormal);
		touchCount = false;
		log("fstUpdate Type 1 Activate !!");
	}
	if (type == 2) {
		itemName = itemCreate(dayChanger, weatherCount);
		auto fstHangAnim = animCreate->CreateAnim("Sprites/FishingStat_hang.json", "FishingStat", 4, 0.1f);
		auto fstHangAnimate = Animate::create(fstHangAnim);
		repFstHang = Repeat::create(fstHangAnimate, 1);
		fstUpdate->runAction(repFstHang);

		log("prg type 3 ");
		auto prgHangAnim = animCreate->CreateAnim("Sprites/FishBowl_hang.json", "fishbowl", 9, 0.1f);
		auto prgHangAnimate = Animate::create(prgHangAnim);
		repPrgHang = Repeat::create(prgHangAnimate, 1);
		seqPrgHang = Sequence::createWithTwoActions(repPrgHang, repPrgHang->reverse());
		seqRepPrgHang = RepeatForever::create(seqPrgHang);
		prgHangBack->setVisible(true);
		prgHangBack->runAction(seqRepPrgHang);

		touchCount = true;
		log("fstUpdate Type 2 Activate !!");
	}
	if (type == 3) {
		//물고기 낚이는 부분 (ropeRemove 수정 필요)
		resultCount = true;
		addNewSpriteAt(Vec2(winSize.width / 2, winSize.height / 2), itemName.c_str(), 2);
		fishBowlProgress(1);
		auto fstSuccessAnim = animCreate->CreateAnim("Sprites/FishingStat_success.json", "FishingStat", 4, 0.1f);
		auto fstSuccessAnimate = Animate::create(fstSuccessAnim);
		repFstSuccess = Repeat::create(fstSuccessAnimate, 1);
		fstUpdate->runAction(repFstSuccess);
		touchCount = false;
		this->scheduleOnce(schedule_selector(LSFGame::touchCounter), 3.f);
		log("fstUpdate Type 3 Activate !!");
	}
	if (type == 4) {
		//물고기 낚시 실패 (ropeRemove 수정 필요)
		resultCount = false;
		addNewSpriteAt(Vec2::ZERO, itemName.c_str(), 1);
		fishBowlProgress(2);
		touchCount = false;
		auto fstFailAnim = animCreate->CreateAnim("Sprites/FishingStat_fail.json", "FishingStat", 4, 0.1f);
		auto fstFailAnimate = Animate::create(fstFailAnim);
		repFstFail = Repeat::create(fstFailAnimate, 1);
		fstUpdate->runAction(repFstFail);
		this->scheduleOnce(schedule_selector(LSFGame::touchCounter), 3.f);
		log("fstUpdate Type 4 Activate !!");
	}
}
void LSFGame::doChangeMode(Ref* pSender)
{
	if (modeSwitch == false) {
		modeSwitch = true;
		btn_modeswitch->selected();
		//manualLayer->setVisible(true);

	}
	else {
		modeSwitch = false;
		btn_modeswitch->unselected();
		//manualLayer->setVisible(false);
		joystick->setVisible(false);
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


void LSFGame::fishBowlProgress(int type)
{
	prgCounter = 0;
	//if (prgInit == false) {
	log("prgInit");
	fishBowl = Sprite::create("Sprites/FishBowl.png");
	fishBowl->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
	fishBowl_fail = Sprite::create("Sprites/FishBowl_fail.png");

	fishingPrg_S = ProgressTimer::create(fishBowl);
	fishingPrg_S->setType(ProgressTimer::Type::BAR);
	fishingPrg_S->setMidpoint(Vec2(0, 0));
	fishingPrg_S->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
	fishingPrg_S->setBarChangeRate(Vec2(0, 1));
	progressLayer->addChild(fishingPrg_S);
	to1 = Sequence::createWithTwoActions(ProgressTo::create(4, 100), ProgressTo::create(0, 40));

	fishingPrg_F = ProgressTimer::create(fishBowl_fail);
	fishingPrg_F->setType(ProgressTimer::Type::BAR);
	fishingPrg_F->setMidpoint(Vec2(0, 0));
	fishingPrg_F->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
	fishingPrg_F->setBarChangeRate(Vec2(0, 1));
	progressLayer->addChild(fishingPrg_F);
	to2 = Sequence::createWithTwoActions(ProgressTo::create(4, 100), ProgressTo::create(0, 40));

	if (type == 1) {
		prgCounter = 1;
		log("prg type 1 ");
		progressLayer->addChild(fishBowl);

		hangItem = Sprite::create(itemName.c_str());
		hangItem->setScale(3.f);
		hangItem->setPosition(Vec2(winSize.width / 2 - 6, winSize.height / 2 + 150));
		progressLayer->addChild(hangItem);

		auto actionFloat2 = ActionFloat::create(3.f, 6, 1.5f, [this](float value) {
			hangItem->setScale(value);
		});
		hangItem->runAction(actionFloat2);

		auto properties = Properties::createNonRefCounted("Materials/2d_effects.material#sample");
		printProperties(properties, 0);
		Material *mat1 = Material::createWithProperties(properties);

		hangItem->setGLProgramState(mat1->getTechniqueByName("outline")->getPassByIndex(0)->getGLProgramState());

		this->scheduleOnce(schedule_selector(LSFGame::fishRemove), 4.f);
	}
	else if (type == 2)
	{
		prgCounter = 2;
		log("prg type 2 ");

		auto prgFailAnim = animCreate->CreateAnim("Sprites/FishBowl_fail.json", "FishBowl_fail", 10, 0.2f);
		auto prgFailAnimate = Animate::create(prgFailAnim);
		repPrgFail = Repeat::create(prgFailAnimate, 1);

		prgFailBack->setVisible(true);
		prgFailBack->runAction(repPrgFail);

	}

}
void LSFGame::fishRemove(float dt)
{
	log("fishRemoveInit");
	if (hangItem->getNumberOfRunningActions() == 0 && prgCounter == 1)
	{
		log("fishRemove 1");
		progressLayer->removeChild(hangItem);
		progressLayer->removeChild(fishBowl);
	}
}

static void printProperties(Properties* properties, int indent)
{
	// Print the name and ID of the current namespace.
	const char* spacename = properties->getNamespace();
	const char* id = properties->getId();
	char chindent[64];
	int i = 0;
	for (i = 0; i < indent * 2; i++)
		chindent[i] = ' ';
	chindent[i] = '\0';

	log("%sNamespace: %s  ID: %s\n%s{", chindent, spacename, id, chindent);

	// Print all properties in this namespace.
	const char* name = properties->getNextProperty();
	const char* value = NULL;
	while (name != NULL)
	{
		value = properties->getString(name);
		log("%s%s = %s", chindent, name, value);
		name = properties->getNextProperty();
	}

	Properties* space = properties->getNextNamespace();
	while (space != NULL)
	{
		printProperties(space, indent + 1);
		space = properties->getNextNamespace();
	}

	log("%s}\n", chindent);
}
LSFGame::~LSFGame()
{
	//월드를 C++의 new로 생성했으므로 여기서 지워준다.
	delete _world;
	_world = nullptr;
}


