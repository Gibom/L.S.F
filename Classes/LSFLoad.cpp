#include "LSFLoad.h"

using namespace cocos2d;

Scene* LSFLoad::createScene()
{
	auto scene = Scene::create();
	auto layer = LSFLoad::create();
	scene->addChild(layer);

	return scene;
}

bool LSFLoad::init()
{
	if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255)))
	{
		return false;
	}

	//////////////////////////////////////////////////////////////////////////
	winSize = Director::getInstance()->getWinSize();

	log("%d", LSFSingleton::getInstance()->value);

	Sprite* back = LSFSingleton::getInstance()->GetmBack();
	back->setAnchorPoint(Vec2(0, 1));
	back->setPosition(Vec2(0, winSize.height));
	this->addChild(back);
	
	back->runAction(LSFSingleton::getInstance()->GetmainRep());
	

	return true;
}