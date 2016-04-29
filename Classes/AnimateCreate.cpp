#include "AnimateCreate.h"
#include "LSFGame.h"

using namespace cocos2d;
using namespace rapidjson;

bool AnimateCreate::init()
{
	init();

	return true;
}

Animation* AnimateCreate::CreateAnim(const std::string & json, const std::string & framename, int frames, float dt)
{
	log("11");
	char frName[20];
	

	auto AnimateFrameCache = SpriteFrameCache::getInstance();
	AnimateFrameCache->addSpriteFramesWithJson(json);
	
	auto CreateAnimation = Animation::create();
	CreateAnimation->setDelayPerUnit(dt);
	log("22");
	for (int frCount = 0; frCount <= frames; frCount++)
	{
	log("33");
	sprintf(frName, "%s %d.png", framename.c_str(), frCount);
	CreateAnimation->addSpriteFrame(AnimateFrameCache->getSpriteFrameByName(frName));
	log("%s", frName);
	}
	CreateAnimation->retain();

	return CreateAnimation;
	
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
		 //return json 파일을 찾지 못했음.
		log("cocos2d: SpriteFrameCache: can not find %s", json.c_str());
		return;
	}
	std::string data = FileUtils::getInstance()->getStringFromFile(fullPath);
	//build texture path by replacing file extension
	std::string texturePath = json;
	//remove .xxx
	size_t startPos = texturePath.find_last_of(".");
	texturePath = texturePath.erase(startPos);
	//append .png
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
				//remove .xxx
				size_t startPos = spriteFrameName.find_last_of(".");
				spriteFrameName = spriteFrameName.erase(startPos);
				//append .png
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
				//check ow/oh
				if (!ow || !oh)
				{
					CCLOGWARN("cocos2d: WARNING: originalWidth/Height not found on the SpriteFrame. AnchorPoint won't work as expected. Regenrate the .json");
				}
				//abs ow/oh
				ow = abs(ow);
				oh = abs(oh);
				//create frame
				SpriteFrame* sprFrame = SpriteFrame::createWithTexture(texture,
					Rect(x, y, w, h),
					false,
					Vec2(ox, oy),
					Size((float)ow, (float)oh)
					);
				//add sprite frame
				//log("%s\n", spriteFrameName.c_str());
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
