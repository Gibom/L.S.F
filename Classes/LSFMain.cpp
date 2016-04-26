#include "LSFMain.h"
#include "LSFGame.h"

using namespace cocos2d;
using namespace rapidjson;


Scene* LSFMain::createScene()
{
	auto scene = Scene::create();
	auto layer = LSFMain::create();
	scene->addChild(layer);

	return scene;
}

bool LSFMain::init()
{
	if (!LayerColor::initWithColor(Color4B(0, 0, 0, 255)))
	{
		return false;
	}

	/////////////////////////////

	//스프라이트 캐시
	auto backFrameCache = SpriteFrameCache::getInstance();
	backFrameCache->addSpriteFramesWithJson("Sprites/Main.json");

	Sprite* back = Sprite::createWithSpriteFrame(backFrameCache->getSpriteFrameByName("Main 0.png"));
	back->setAnchorPoint(Vec2::ZERO);
	back->setPosition(Vec2(0, 0));
	back->setScale(0.5f);
	this->addChild(back);

	auto logoFrameCache = SpriteFrameCache::getInstance();
	logoFrameCache->addSpriteFramesWithJson("Sprites/Logo.json");

	Sprite* logo = Sprite::createWithSpriteFrame(logoFrameCache->getSpriteFrameByName("Logo 0.png"));
	logo->setAnchorPoint(Vec2::ZERO);
	logo->setPosition(Vec2(0, 0));
	logo->setScale(0.5f);
	this->addChild(logo);

	//메뉴
	btn_Start = MenuItemImage::create("Sprites/Button_start_up.png",
									  "Sprites/Button_start_down.png",
									  CC_CALLBACK_1(LSFMain::doPushSceneTran, this));
	
	auto startMenu = Menu::create(btn_Start, nullptr);
	startMenu->setAnchorPoint(Vec2(0.5, 0.5));
	//startMenu->setPosition(Vec2(365, 300));
	startMenu->setPosition(Vec2(80, 40));
	startMenu->setScale(0.5f);
	startMenu->alignItemsHorizontally();
	
	this->addChild(startMenu);


	//애니메이션 - (코드 개선 작업 시 addSpriteFramesWithJson 함수에서 for 문으로 animation 생성하는 기능 추가, animation 생성여부 파라미터 bool값으로 )
	
	//Background
	auto mainBackgroundAnimation = Animation::create();
	mainBackgroundAnimation->setDelayPerUnit(0.1f);
	mainBackgroundAnimation->addSpriteFrame(backFrameCache->getSpriteFrameByName("Main 0.png"));
	mainBackgroundAnimation->addSpriteFrame(backFrameCache->getSpriteFrameByName("Main 1.png"));
	mainBackgroundAnimation->addSpriteFrame(backFrameCache->getSpriteFrameByName("Main 2.png"));
	mainBackgroundAnimation->addSpriteFrame(backFrameCache->getSpriteFrameByName("Main 3.png"));
	mainBackgroundAnimation->addSpriteFrame(backFrameCache->getSpriteFrameByName("Main 4.png"));
	mainBackgroundAnimation->addSpriteFrame(backFrameCache->getSpriteFrameByName("Main 5.png"));
	mainBackgroundAnimation->addSpriteFrame(backFrameCache->getSpriteFrameByName("Main 6.png"));
	mainBackgroundAnimation->addSpriteFrame(backFrameCache->getSpriteFrameByName("Main 7.png"));
	mainBackgroundAnimation->addSpriteFrame(backFrameCache->getSpriteFrameByName("Main 8.png"));
	mainBackgroundAnimation->addSpriteFrame(backFrameCache->getSpriteFrameByName("Main 9.png"));
	mainBackgroundAnimation->addSpriteFrame(backFrameCache->getSpriteFrameByName("Main 10.png"));
	mainBackgroundAnimation->addSpriteFrame(backFrameCache->getSpriteFrameByName("Main 11.png"));
	mainBackgroundAnimation->addSpriteFrame(backFrameCache->getSpriteFrameByName("Main 12.png"));
	mainBackgroundAnimation->addSpriteFrame(backFrameCache->getSpriteFrameByName("Main 13.png"));
	mainBackgroundAnimation->addSpriteFrame(backFrameCache->getSpriteFrameByName("Main 14.png"));
	mainBackgroundAnimation->addSpriteFrame(backFrameCache->getSpriteFrameByName("Main 15.png"));
	mainBackgroundAnimation->addSpriteFrame(backFrameCache->getSpriteFrameByName("Main 16.png"));
	mainBackgroundAnimation->addSpriteFrame(backFrameCache->getSpriteFrameByName("Main 17.png"));
	mainBackgroundAnimation->addSpriteFrame(backFrameCache->getSpriteFrameByName("Main 18.png"));
	mainBackgroundAnimation->addSpriteFrame(backFrameCache->getSpriteFrameByName("Main 19.png"));
	mainBackgroundAnimation->addSpriteFrame(backFrameCache->getSpriteFrameByName("Main 20.png"));
	mainBackgroundAnimation->retain();

	//Logo
	auto mainLogoAnimation = Animation::create();
	mainLogoAnimation->setDelayPerUnit(0.1f);
	mainLogoAnimation->addSpriteFrame(logoFrameCache->getSpriteFrameByName("Logo 0.png"));
	mainLogoAnimation->addSpriteFrame(logoFrameCache->getSpriteFrameByName("Logo 1.png"));
	mainLogoAnimation->addSpriteFrame(logoFrameCache->getSpriteFrameByName("Logo 2.png"));
	mainLogoAnimation->addSpriteFrame(logoFrameCache->getSpriteFrameByName("Logo 3.png"));
	mainLogoAnimation->addSpriteFrame(logoFrameCache->getSpriteFrameByName("Logo 4.png"));
	mainLogoAnimation->addSpriteFrame(logoFrameCache->getSpriteFrameByName("Logo 5.png"));
	mainLogoAnimation->addSpriteFrame(logoFrameCache->getSpriteFrameByName("Logo 6.png"));
	mainLogoAnimation->addSpriteFrame(logoFrameCache->getSpriteFrameByName("Logo 7.png"));
	mainLogoAnimation->addSpriteFrame(logoFrameCache->getSpriteFrameByName("Logo 8.png"));
	mainLogoAnimation->addSpriteFrame(logoFrameCache->getSpriteFrameByName("Logo 9.png"));
	mainLogoAnimation->addSpriteFrame(logoFrameCache->getSpriteFrameByName("Logo 10.png"));
	mainLogoAnimation->addSpriteFrame(logoFrameCache->getSpriteFrameByName("Logo 11.png"));
	mainLogoAnimation->addSpriteFrame(logoFrameCache->getSpriteFrameByName("Logo 12.png"));
	mainLogoAnimation->addSpriteFrame(logoFrameCache->getSpriteFrameByName("Logo 13.png"));
	mainLogoAnimation->addSpriteFrame(logoFrameCache->getSpriteFrameByName("Logo 14.png"));
	mainLogoAnimation->addSpriteFrame(logoFrameCache->getSpriteFrameByName("Logo 15.png"));
	mainLogoAnimation->addSpriteFrame(logoFrameCache->getSpriteFrameByName("Logo 16.png"));
	mainLogoAnimation->addSpriteFrame(logoFrameCache->getSpriteFrameByName("Logo 17.png"));
	mainLogoAnimation->addSpriteFrame(logoFrameCache->getSpriteFrameByName("Logo 18.png"));
	mainLogoAnimation->addSpriteFrame(logoFrameCache->getSpriteFrameByName("Logo 19.png"));
	mainLogoAnimation->addSpriteFrame(logoFrameCache->getSpriteFrameByName("Logo 20.png"));
	mainLogoAnimation->retain();

	////애니메이션 실행

	//Background
	auto backAnimate = Animate::create(mainBackgroundAnimation);
	auto rep = RepeatForever::create(backAnimate);

	//Logo
	auto logoAnimate = Animate::create(mainLogoAnimation);
	auto delayLogo = DelayTime::create(5.f);
	auto seqLogo = Sequence::create(logoAnimate, delayLogo, nullptr);
	auto seqLogoRep = RepeatForever::create(seqLogo);
	logo->runAction(seqLogoRep);
	back->runAction(rep);

	return true;
}

//Aseprite -> Json으로 Export한 것을 Parsing하는 함수 생성[addSpriteFramesWithJson(const std::string & json)]
//CCSpriteFrameCache.h에 'void addSpriteFramesWidthJson(const std::string & json);' 추가하고 여기서 정의함
//CCSpriteFrameCache.cpp에 따로 정의하지 않았음(할필요없음..)
void SpriteFrameCache::addSpriteFramesWithJson(const std::string & json)
{
	CCASSERT(json.size() > 0, "json filename should not be nullptr");
	std::string fullPath = FileUtils::getInstance()->fullPathForFilename(json);
	if (fullPath.size() == 0)
	{
		// return json 파일을 찾지 못했음.
		log("cocos2d: SpriteFrameCache: can not find %s", json.c_str());
		return;
	}
	std::string data = FileUtils::getInstance()->getStringFromFile(fullPath);
	// build texture path by replacing file extension
	std::string texturePath = json;
	// remove .xxx
	size_t startPos = texturePath.find_last_of(".");
	texturePath = texturePath.erase(startPos);
	// append .png
	texturePath = texturePath.append(".png");
	Texture2D *texture = Director::getInstance()->getTextureCache()->addImage(texturePath.c_str());
	texture->setAliasTexParameters();
	if (texture)
	{
		Document document;
		if (!document.Parse<0>(data.c_str()).HasParseError())
		{
			const rapidjson::Value& documentFrames = document["frames"];
			for (SizeType i = 0; i < documentFrames.Size(); i++)
			{
				std::string spriteFrameName = documentFrames[i]["filename"].GetString();
				// remove .xxx
				size_t startPos = spriteFrameName.find_last_of(".");
				spriteFrameName = spriteFrameName.erase(startPos);
				// append .png
				spriteFrameName = spriteFrameName.append(".png");

				SpriteFrame* spriteFrame = _spriteFrames.at(spriteFrameName);
				float x = static_cast<float>(documentFrames[i]["frame"]["x"].GetDouble());
				float y = static_cast<float>(documentFrames[i]["frame"]["y"].GetDouble());
				float w = static_cast<float>(documentFrames[i]["frame"]["w"].GetDouble());
				float h = static_cast<float>(documentFrames[i]["frame"]["h"].GetDouble());
				float ox = static_cast<float>(documentFrames[i]["spriteSourceSize"]["x"].GetDouble());
				float oy = static_cast<float>(documentFrames[i]["spriteSourceSize"]["y"].GetDouble());
				float ow = static_cast<float>(documentFrames[i]["spriteSourceSize"]["w"].GetDouble());
				float oh = static_cast<float>(documentFrames[i]["spriteSourceSize"]["h"].GetDouble());
				// check ow/oh
				if (!ow || !oh)
				{
					CCLOGWARN("cocos2d: WARNING: originalWidth/Height not found on the SpriteFrame. AnchorPoint won't work as expected. Regenrate the .json");
				}
				// abs ow/oh
				ow = abs(ow);
				oh = abs(oh);
				// create frame
				SpriteFrame* sprFrame = SpriteFrame::createWithTexture(texture,
					Rect(x, y, w, h),
					false,
					Vec2(ox, oy),
					Size((float)ow, (float)oh)
					);
				// add sprite frame
				log("%s\n", spriteFrameName.c_str());
				_spriteFrames.insert(spriteFrameName, sprFrame);
			}
		}
		else
		{
			log("cocos2d: SpriteFrameCache: Couldn't load texture");
		}
		_loadedFileNames->insert(json);
	}
}
void LSFMain::doPushSceneTran(Ref * pSender)
{
	auto pScene = LSFGame::createScene();
	
	Director::getInstance()->replaceScene(createTransition(7, 1, pScene));
	
}
TransitionScene* LSFMain::createTransition(int nIndex, float t, Scene* s)
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



