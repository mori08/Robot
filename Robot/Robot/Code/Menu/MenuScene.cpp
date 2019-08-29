#include "MenuScene.h"
#include "MenuManager.h"


namespace
{
	const int MAX_GENERATE_FRAME_COUNT = 240; // �������܂ł̎��Ԃ̍ő�l
	const int MIN_GENERATE_FRAME_COUNT = 60;  // �������܂ł̎��Ԃ̍ŏ��l
}


Robot::MenuScene::MenuScene()
	: _generateLightFrameCount(0)
{
	
}


void Robot::MenuScene::update()
{
	if (--_generateLightFrameCount <= 0)
	{
		_lightList.emplace_back(TitleLight::get());

		_generateLightFrameCount = Random(MIN_GENERATE_FRAME_COUNT, MAX_GENERATE_FRAME_COUNT);
	}

	for (auto & light : _lightList)
	{
		light.update();
	}

	Erase_if(_lightList, [](TitleLight & light) {return light.isEraseAble(); }); Erase_if(_lightList, [](TitleLight & light) {return light.isEraseAble(); });

	MenuManager::Instance().update();

	String sceneName, sceneInfo;
	if (MenuManager::Instance().isChangeAbleScene(sceneName, sceneInfo))
	{
		m_data->sceneInfo = sceneInfo;
		changeScene(sceneName);
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
