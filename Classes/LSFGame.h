#ifndef __LSFGame_SCENE_H__
#define __LSFGame_SCENE_H__

#include "cocos2d.h"
#include "Box2D\Box2D.h"
#include <GLES-Render.h>
#include "vrope.h"
#include "Joystick.h"
#include "ContactListener.h"
#include "AnimateCreate.h"
#include "WaterNode.h"
#include "Inventory.h"
#include "LSFSingleton.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"


using namespace cocos2d;

class LSFGame : public cocos2d::LayerColor , public AnimateCreate 

{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(LSFGame);

	void doRain();
	void doSnow();
	void doRing();
	Sprite* _background;
	void particleRemove(float dt);

	//Box2D-Start---------------------------------------------------------------------------
	bool createBox2dWorld(bool debug);
	SpriteBatchNode* ropeSpriteSheet;
	~LSFGame();

	b2Body *groundBody;
	void tick(float dt);
	
	virtual void draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform, uint32_t flags) override;

	//사운드
	void SoundDelay(float dt);
	int sDelayCheck = 0;
	int soundCheck = 0;
	//상태바 (날씨, 시간등 환경정보 표시)
	Sprite* WStatBack;

	//아이템 생성
	std::string itemName;
	std::string itemCreate(int day, int weather);
	float bonus;		//추가확률
	int chance;			//확률
	int rarity;			//희귀도
	int kindof;			//종류 장비(1), 소모품(2), 물고기(3)
	
	
	Vec2 touchPoint; // onTouchBegan touchpoint

	//조합
	bool tableComplete;
	bool bTouch_table;
	bool moveCheck;
	int tmpCount = 0;
	int craftInit = 0;
	TableViewCell* temp1;
	TableViewCell* temp2;
	Sprite* craftTmp1;
	Sprite* craftTmp2;
	void combine(int itemA, int itemB, TableViewCell* cellA, TableViewCell* cellB);
	Sprite* btnCraft;
	int temp1Tag = -1;
	int temp2Tag = -1;
	Sprite* invNull;
	int tableTag = 0;
	int cellIdx = 0;
	int cellTag = 0;

	//낚시
	b2Body* needle;
	b2Body* fish;
	b2BodyDef needlebodyDef; 
	b2FixtureDef needlefixtureDef;
	b2Body* addNewSpriteAt(Vec2 point, const std::string & imagepath, int tag);
	b2Body* addNewSpriteAt(b2Vec2 point, const std::string & imagepath, int tag);
	b2Body* needleBody;
	b2Body* fishBody;
	Sprite* addFish;
	Sprite* hangItem;
	void createRope(b2Body* bodyA, b2Vec2 anchorA, b2Body* bodyB, b2Vec2 anchorB, float32 sag);
	std::vector<VRope*>* ropes;
	void items(int tag);
	void ropeTick(float dt);
	void waterSplash(float dt);
	void ropeRemove(int type);
	Vec2 touchRope;
	float32 ropeLength;
	
	//낚시 - Timer
	void startFishing(float dt);
	void timerFishing(float dt);
	void endFishing(float dt);
	void catchFishing(float dt);
	void resetFishing();
	int catchTime;
	int randomTime;
	int timer;

	//낚시 - 조작
	float fishingGauge;
	bool bTouch_mode; //모드 스위치 구현 시 사용
	bool hangFish;
	void doChangeMode(Ref* pSender);
	Joystick* joystick;

	//프로그레스
	Sprite* TimerBack;
	Sprite* Timer;
	int TimerPer = 434;
	Sprite* GaugeBack;
	Sprite* Gauge;
	int GaugePer = 0;
	bool prgInit = false;
	Sprite* prgHangBack;
	Sprite* prgFailBack;
	Sprite* fishBowl;
	Sprite* fishBowl_fail;
	void fishBowlProgress(int type);
	ProgressTimer* fishingPrg_S;
	ProgressTimer* fishingPrg_F;
	Sequence* to1;
	Sequence* to2;
	void fishRemove(float dt);
	int prgCounter;

	//충돌처리
	b2Body* createRopeTipBody();
	ContactListener* myContactListener;
	b2Body* shipBody;
	
	//날씨
	WaterNode* water;
	int weatherCount;
	
	Vector<Sprite*> flow;

	Texture2D* texture;
	b2World* _world;
	GLESDebugDraw* m_debugDraw;

	//Box2D-End---------------------------------------------------------------------------

	//환경구성

	//option
	bool optCount;
	LayerColor* OptionLayer;
	MenuItemImage* btn_Option;
	MenuItemImage* btn_Close;
	Menu* mainMenu;
	Menu* optionMenu;

	Sprite* optionBoard;
	void doOption(Ref * pSender);
	void sliderEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);
	cocos2d::ui::Text* _displayValueLabel;
	cocos2d::ui::Text* _displayValueLabel2;

	//WorldTimer
	void WorldTimer(float dt);
	void dayChangerF(int type);
	int wTime = 0;	// 1wTime = 1gmin = 2.5sec
	int wtInit;
	int dayChanger = 0;
	//WorldChange
	//day
	Sprite* backDefault;
	Animation* mainAnim;
	Animate* mainAnimate;
	RepeatForever* repMain;

	//Animation
	AnimateCreate* animCreate;
	RepeatForever* repFstNormal;
	Repeat* repPrgHang;
	RepeatForever* seqRepPrgHang;
	Sequence* seqPrgHang;

	Repeat* repPrgFail;

	Repeat* repFstHang;
	Repeat* repFstSuccess;
	Repeat* repFstFail;

	void fstChange(int type);


	//World
	Size winSize;
	Sprite* back;
	Sprite* ship;
	Sprite* fisherman;
	Sprite* fstUpdate;
	Sprite* inventory;
	Sprite* craftUsel;
	Sprite* craftSel;
	Sprite* craft;
	
	
	Sprite* rainDrop;
	Sprite* snowDrop;
	LayerColor* StatLayer;
	LayerColor* invenLayer;
	LayerColor* manualLayer;
	LayerColor* progressLayer;
	MenuItemImage* btn_inventory;
	Menu* inventoryMenu;
	MenuItemImage* btn_modeswitch;
	Menu* modeswitchMenu;
	b2Body* water1;
	b2Body* water2;
	b2Body* water3;
	//World - Flow
	b2Body* addNewSpriteFlow(Vec2 point, Size size, b2BodyType bodytype, int flowtype, int type);
	b2WheelJoint* m_spring1;
	b2WheelJoint* m_spring2;
	b2WheelJoint* m_spring3;
	b2WheelJoint* m_spring4;
	b2WheelJoint* m_spring5;
	b2WheelJoint* m_spring6;
	b2WheelJoint* m_spring7;
	b2WheelJoint* m_spring8;

	b2WheelJointDef flowJd1;
	b2WheelJointDef flowJd2;
	b2WheelJointDef flowJd3;
	b2WheelJointDef flowJd4;
	b2WheelJointDef flowJd5;
	b2WheelJointDef flowJd6;
	b2WheelJointDef flowJd7;
	b2WheelJointDef flowJd8;
	b2Body *flowBody0;
	b2Body *flowBody1;
	b2Body *flowBody2;
	b2Body *flowBody3;
	b2Body *flowBody4;
	b2Body *flowBody5;
	b2Body *flowBody6;
	b2Body *flowBody7;
	b2Body *flowBody8;
	b2Body *flowBody9;
	b2Body *flowBody10;
	b2Body *flowBody11;



	b2Vec2 axis;

	//상태변화  WeatherStatus - Normal(1), Windy(2), Snowy(3), Rainny(4), ThunderStorm(5)
	int statusCheck(const std::string & kindof);
	int ShipStat;



	bool playerIsFlying = false;
	float playerVelocity = 0;
	RepeatForever* rainRep;
	//Ship
	SpriteFrameCache* ShipFrameCache;
	RepeatForever* shipRep;
	
	//가방
	Inventory* inv;
	Size invSize;
	Vec2 invPosition;
	Sprite* invOpen;
	std::vector <TableView*> invTable;
	MenuItemImage* inv1;
	MenuItemImage* inv2;
	MenuItemImage* inv3;
	Menu* invTab;
	Animation* invenAnim;
	Animate* invenAnimate;
	Repeat* repInven;
	int lastSel = 0;

	//카운트
	int cbtnCount;
	int waterCount;
	int flowRand;
	int flowCount = 0;
	int fstCount = 0;
	int hBonus = 0;
	
	bool resultCount;
	bool btnCount;
	bool invOpenCount = false;
	bool touchCount;
	bool ropeTickCount;
	bool ropeTouchCount;
	
	bool craftSwitch;
	bool modeSwitch;
	void touchCounter(float dt);
	
	//virtual void onEnter();
	//virtual void onExit();
	EventListenerTouchOneByOne* listener;
	virtual bool onTouchBegan(Touch* touch, Event* event);
	virtual void onTouchMoved(Touch* touch, Event* event);
	virtual void onTouchEnded(Touch* touch, Event* event);

	//Inventory 
	void doPushInventory(Ref * pSender);
	void doPushInvTab(Ref * pSender);
	
	//cocos2d::TransitionScene* createTransition(int nIndex, float t, cocos2d::Scene* s);

protected:
	void onDraw(const cocos2d::Mat4& transform, uint32_t flags);
	cocos2d::CustomCommand _customCommand;
};

#endif // __LSFGame_SCENE_H__
