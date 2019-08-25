#include "MenuScene.h"
#include "Window\MainWindow.h"
#include "Window\StageWindow.h"
#include "Window\DiaryWindow.h"


namespace
{
	const int STAGE_NUM = 10; // ステージ数

	const int MAX_GENERATE_FRAME_COUNT = 240; // 光生成までの時間の最大値
	const int MIN_GENERATE_FRAME_COUNT = 60;  // 光生成までの時間の最小値
}


Robot::MenuScene::MenuScene()
	: _generateLightFrameCount(0)
{
	_windowMap[L"Main"]  = std::make_shared<MainWindow>(*this);
	_windowMap[L"Stage"] = std::make_shared<StageWindow>(*this);
	_windowMap[L"Diary"] = std::make_shared<DiaryWindow>(*this);

	_selectedWindowName = L"Main";
	
	_windowMap[_selectedWindowName]->open();
	_windowMap[_selectedWindowName]->updateInputManager();
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

	for (auto & window : _windowMap)
	{
		window.second->update();
	}
}


void Robot::MenuScene::draw() const
{
	for (const auto & light : _lightList)
	{
		light.draw();
	}

	for (const auto & window : _windowMap)
	{
		window.second->draw();
	}
}


void Robot::MenuScene::openWindow(const String & windowName)
{
	if (_windowMap.find(windowName) == _windowMap.end()) { return; }

	_windowMap[_selectedWindowName]->nonSelect();
	_windowMap[windowName]->open();
	_windowMap[windowName]->updateInputManager();
	_selectedWindowName = windowName;
}


void Robot::MenuScene::closeWindow(const String & windowName)
{
	if (_windowMap.find(windowName) == _windowMap.end()) { return; }

	_windowMap[_selectedWindowName]->close();
	_windowMap[windowName]->select();
	_windowMap[windowName]->updateInputManager();
	_selectedWindowName = windowName;
}
