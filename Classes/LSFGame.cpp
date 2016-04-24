#include "LSFGame.h"
#include "cocos2d\external\json\rapidjson.h"
#include "cocos2d\external\json\document.h"
#include "cocos2d\external\json\stringbuffer.h"
#include "cocos2d\external\json\writer.h"

using namespace cocos2d;
using namespace rapidjson;


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
	//스프라이트 캐시
	auto backFrameCache = SpriteFrameCache::getInstance();
	backFrameCache->addSpriteFramesWithJson("Sprites/Game.json");

	Sprite* back = Sprite::createWithSpriteFrame(backFrameCache->getSpriteFrameByName("Game 0.png"));
	back->setAnchorPoint(Vec2::ZERO);
	back->setPosition(Vec2(0, -110));
	//back->setScaleY(0.8f);
	this->addChild(back);


	return true;
}

