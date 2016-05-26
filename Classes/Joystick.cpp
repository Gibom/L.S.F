//
//  Joystick.cpp
//  JoyStickEx
//
//  Created by Jaewhan Lee on 13. 6. 5..
//  Copyright www.cocos2d-x.kr 2013년. All rights reserved.
//

#include "Joystick.h"
#include "ui/CocosGUI.h"


using namespace cocos2d;

static void printProperties(Properties* properties, int indent);

#define JOYSTICK_OFFSET_X 5.0f
#define JOYSTICK_OFFSET_Y 5.0f

#define JOYSTICK_RADIUS 120.0f
#define THUMB_RADIUS 26.0f

static bool isPointInCircle(Vec2 point, Vec2 center, float radius)
{
    float dx = (point.x - center.x);
    float dy = (point.y - center.y);
    return (radius >= sqrt((dx*dx)+(dy*dy)));
}

bool Joystick::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

    //////////////////////////////////////////////////////////////////////////
	winSize = Director::getInstance()->getWinSize();
    /*kCenter = Vec2(JOYSTICK_RADIUS + JOYSTICK_OFFSET_X, JOYSTICK_RADIUS + JOYSTICK_OFFSET_Y);*/

	//kCenter = Vec2(338, 240);
	kCenter = Vec2(winSize.width/2, winSize.height/3);
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesBegan = CC_CALLBACK_2(Joystick::onTouchesBegan, this);
    listener->onTouchesMoved = CC_CALLBACK_2(Joystick::onTouchesMoved, this);
    listener->onTouchesEnded = CC_CALLBACK_2(Joystick::onTouchesEnded, this);
    listener->onTouchesCancelled = CC_CALLBACK_2(Joystick::onTouchesCancelled, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    velocity = Vec2::ZERO;

	auto properties = Properties::createNonRefCounted("Materials/auto_binding_test.material#sample");
	// Print the properties of every namespace within this one.
	printProperties(properties, 0);

	Material *mat1 = Material::createWithProperties(properties);

	auto spriteOutline = Sprite::create("Sprites/joystick_background.png");
	spriteOutline->setPosition(kCenter);
	spriteOutline->setScale(1.4f);
	this->addChild(spriteOutline);
	spriteOutline->setGLProgramState(mat1->getTechniqueByName("outline")->getPassByIndex(0)->getGLProgramState());
	spriteOutline->stopAllActions();
	// properties is not a "Ref" object
	CC_SAFE_DELETE(properties);

	auto JoystickFrameCache = SpriteFrameCache::getInstance();
	JoystickFrameCache->addSpriteFramesWithJson("Sprites/Joystick.json");

	bg = Sprite::createWithSpriteFrame(JoystickFrameCache->getSpriteFrameByName("Joystick 0.png"));
	bg->setPosition(kCenter);
	bg->setScale(1.4f);
	this->addChild(bg);



  /*  bg = Sprite::create("Sprites/joystick_background.png");
    bg->setPosition(kCenter);
    this->addChild(bg, 0);*/
    
    thumb = Sprite::create("Sprites/joystick_thumb.png");
    thumb->setPosition(kCenter);
    this->addChild(thumb, 1);

	Joystick::onEnter();
	

    return true;
}

void Joystick::updateVelocity(Vec2 point)
{
    // calculate Angle and length
    float dx = point.x - kCenter.x;
    float dy = point.y - kCenter.y;
    
    float distance = sqrt(dx*dx + dy*dy);
    float angle = atan2(dy,dx); // in radians
    
    if (distance > JOYSTICK_RADIUS)
    {
        dx = cos(angle) * JOYSTICK_RADIUS;
        dy = sin(angle) * JOYSTICK_RADIUS;
    }
    
    velocity = Vec2(dx/JOYSTICK_RADIUS, dy/JOYSTICK_RADIUS);
    
    if (distance>THUMB_RADIUS)
    {
        point.x = kCenter.x + cos(angle) * THUMB_RADIUS;
        point.y = kCenter.y + sin(angle) * THUMB_RADIUS;
    }
    
    thumb->setPosition(point);
}

void Joystick::resetJoystick()
{
    this->updateVelocity(kCenter);
}

bool Joystick::handleLastTouch()
{
    bool wasPressed = isPressed;
    if (wasPressed)
    {
        this->resetJoystick();
        isPressed = false;
    }
    return (wasPressed ? true : false);
}

void Joystick::onTouchesBegan(const std::vector<Touch*>& touches, Event  *event)
{

	log("joy touch1");
	Touch* touch = touches[0];
    Vec2 touchPoint = touch->getLocation();
	log("joy touchPoint x: %f y: %f", touchPoint.x, touchPoint.y);
	log("joy kCenter x: %f y: %f", kCenter.x, kCenter.y);
    if (isPointInCircle(touchPoint, kCenter, JOYSTICK_RADIUS))
    {


		log("joy touch2");
        isPressed = true;
        this->updateVelocity(touchPoint);
		doJoyAnimate(1);
		soundEffect->doSoundAction("game", 17);
    }
}

void Joystick::onTouchesMoved(const std::vector<Touch*>& touches, Event  *event)
{
	log("joy moved 1\nisPressed: %d", isPressed);
    if (isPressed)
    {
		log("joy moved 2");
		
        Touch* touch = touches[0];
        Vec2 touchPoint = touch->getLocation();
        this->updateVelocity(touchPoint);
		
		log("fishingGauge: %d", fishingGauge);
		fishingGauge+= 4;
		
    }
}

void Joystick::onTouchesEnded(const std::vector<Touch*>& touches, Event  *event)
{
	log("joy Ended");
	doJoyAnimate(2);
    this->handleLastTouch();
}

void Joystick::onTouchesCancelled(const std::vector<Touch*>& touches, Event  *event)
{
	log("joy Cancelled");
    this->handleLastTouch();
}

void Joystick::doJoyAnimate(int type)
{
	if(type == 1){
		joystickAnim = animCreate->CreateAnim("Sprites/Joystick.json", "Joystick", 15, 0.05f);
		joystickAnimate = Animate::create(joystickAnim);
		repJoystick = RepeatForever::create(joystickAnimate);
		bg->runAction(repJoystick);
	}
	else {
		bg->stopAllActions();
	}
	
}

class EffectAutoBindingResolver : public GLProgramState::AutoBindingResolver
{
	bool resolveAutoBinding(GLProgramState* glProgramState, Node* node, const std::string& uniform, const std::string& autoBinding);

	void callbackRadius(GLProgram* glProgram, Uniform* uniform);
	void callbackColor(GLProgram* glProgram, Uniform* uniform);
};

bool EffectAutoBindingResolver::resolveAutoBinding(GLProgramState* glProgramState, Node* node, const std::string& uniform, const std::string& autoBinding)
{
	if (autoBinding.compare("DYNAMIC_RADIUS") == 0)
	{
		glProgramState->setUniformCallback(uniform, CC_CALLBACK_2(EffectAutoBindingResolver::callbackRadius, this));
		return true;
	}
	else if (autoBinding.compare("OUTLINE_COLOR") == 0)
	{
		glProgramState->setUniformCallback(uniform, CC_CALLBACK_2(EffectAutoBindingResolver::callbackColor, this));
		return true;
	}
	return false;
}

void EffectAutoBindingResolver::callbackRadius(GLProgram* glProgram, Uniform* uniform)
{
	float f = CCRANDOM_0_1() * 10;
	glProgram->setUniformLocationWith1f(uniform->location, f);
}

void EffectAutoBindingResolver::callbackColor(GLProgram* glProgram, Uniform* uniform)
{
	float r = CCRANDOM_0_1();
	float g = CCRANDOM_0_1();
	float b = CCRANDOM_0_1();

	glProgram->setUniformLocationWith3f(uniform->location, r, g, b);
}

Joystick::Joystick()
{
	_resolver = new EffectAutoBindingResolver;
}

Joystick::~Joystick()
{
	delete _resolver;
}


static void printProperties(Properties* properties, int indent)
{
	// Print the name and ID of the current namespace.
	const char* spacename = properties->getNamespace();
	const char* id = properties->getId();
	char chindent[64];
	int i = 0;
	for (i = 0; i<indent * 2; i++)
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
