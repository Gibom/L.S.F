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
	//스프라이트 캐시
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

	//가방 레이어 추가
	//가방------------------------------------------------------------------------------------------------
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
	//가방----------------------------------------------------------------------------------------------------


	//환경 구조물배치------------------------------------------------------------------------------------------------

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
	


	//환경 구조물배치------------------------------------------------------------------------------------------------

	//메뉴
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
	////애니메이션 - (코드 개선 작업 시 addSpriteFramesWithJson 함수에서 for 문으로 animation 생성하는 기능 추가, animation 생성여부 파라미터 bool값으로 )

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


	////애니메이션 실행

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

	_eventDispatcher->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);

	Layer::onExit();
}
bool LSFGame::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
	auto touchPoint = touch->getLocation();

	log("onTOuchBegan id = %d, x = %f, y= %f", touch->getID(), touchPoint.x, touchPoint.y);

	//touch check --------------------------------

	bool bTouch_craft = craft->getBoundingBox().containsPoint(touchPoint);
	bool bTouch_mode; //모드 스위치 구현 시 사용
	// 가방이 열려있고 craft가 선택 됐을 때
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