#include "ui/CocosGUI.h"
#include "Material_AutoBindings.h"
#include "cocos2d.h"
using namespace cocos2d;

static void printProperties(Properties* properties, int indent);

//
// MARK: Material_AutoBindings
//

/*
* Custom material auto-binding resolver for terrain.
*/



Scene* Material_AutoBindings::createScene()
{
	auto scene = Scene::create();
	auto layer = Material_AutoBindings::create();
	scene->addChild(layer);

	return scene;
}

bool Material_AutoBindings::init()
{
	if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255)))
	{
		return false;
	}

	/////////////////////////////
	Material_AutoBindings::onEnter();
	return true;
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

Material_AutoBindings::Material_AutoBindings()
{
	_resolver = new EffectAutoBindingResolver;
}

Material_AutoBindings::~Material_AutoBindings()
{
	delete _resolver;
}


void Material_AutoBindings::onEnter()
{
	//    auto properties = Properties::createNonRefCounted("Materials/2d_effects.material#sample");
	auto properties = Properties::createNonRefCounted("Materials/auto_binding_test.material#sample");

	// Print the properties of every namespace within this one.
	printProperties(properties, 0);

	Material *mat1 = Material::createWithProperties(properties);

	auto spriteOutline = Sprite::create("Images/grossini.png");
	spriteOutline->setNormalizedPosition(Vec2(0.4f, 0.5f));
	this->addChild(spriteOutline);
	spriteOutline->setGLProgramState(mat1->getTechniqueByName("outline")->getPassByIndex(0)->getGLProgramState());

	// properties is not a "Ref" object
	CC_SAFE_DELETE(properties);
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
