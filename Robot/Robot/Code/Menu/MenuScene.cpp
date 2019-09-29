#include "MenuScene.h"
#include "MenuManager.h"
#include "../SaveData/SaveDataManager.h"
#include "../MyColor.h"


namespace
{
	const int MAX_GENERATE_FRAME_COUNT = 300; // Œõ¶¬‚Ü‚Å‚ÌŠÔ‚ÌÅ‘å’l
	const int MIN_GENERATE_FRAME_COUNT = 100;  // Œõ¶¬‚Ü‚Å‚ÌŠÔ‚ÌÅ¬’l
}


std::list<Robot::MenuLight> Robot::MenuScene::_lightList;


Robot::MenuScene::MenuScene()
	: _generateLightFrameCount(0)
{
	
}


void Robot::MenuScene::update()
{
	if (!SaveDataManager::Instance().getFlag(L"Stage9")&&--_generateLightFrameCount <= 0)
	{
		_lightList.emplace_back(MenuLight::get());

		_generateLightFrameCount = Random(MIN_GENERATE_FRAME_COUNT, MAX_GENERATE_FRAME_COUNT);
	}

	for (auto & light : _lightList)
	{
		light.update();
	}

	Erase_if(_lightList, [](MenuLight & light) {return light.isEraseAble(); });

	_lightList.sort();

	MenuManager::Instance().update();

	String sceneName, sceneInfo;
	if (MenuManager::Instance().isChangeAbleScene(sceneName, sceneInfo))
	{
		m_data->sceneInfo = sceneInfo;
		changeScene(sceneName);
	}
}


void Robot::MenuScene::updateFadeIn(double)
{
	for (auto & light : _lightList)
	{
		light.update();
	}
}


void Robot::MenuScene::updateFadeOut(double)
{
	for (auto & light : _lightList)
	{
		light.update();
	}
}


void Robot::MenuScene::draw() const
{
	for (const auto & light : _lightList)
	{
		light.draw();
	}

	MenuManager::Instance().draw();
}
