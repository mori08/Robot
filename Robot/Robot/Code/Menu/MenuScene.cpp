#include "MenuScene.h"
#include "Window\MainWindow.h"
#include "Window\StageWindow.h"


namespace
{
	using Processing = std::function<void()>;
	const int STAGE_NUM = 10; // ステージ数
}


Robot::MenuScene::MenuScene()
{
	_windowMap[L"Main"] = std::make_shared<MainWindow>();
	_windowMap[L"Main"]->setClickedProcessing(L"TitleButton", std::make_unique<Processing>([this]() { changeScene(L"TitleScene"); }));
	_windowMap[L"Main"]->setClickedProcessing(L"StageButton", std::make_unique<Processing>([this]() { openWindow(L"Stage"); }));

	_windowMap[L"Stage"] = std::make_shared<StageWindow>();
	for (int i = 0; i < 10; ++i)
	{
		String stageName = L"Stage" + ToString(i);
		_windowMap[L"Stage"]->setClickedProcessing(stageName, std::make_unique<Processing>(
			[this,stageName]() 
			{
				m_data->sceneInfo = stageName;
				changeScene(L"LoadGameScene");
			}
		));
	}

	_selectedWindowName = L"Main";
	
	_windowMap[_selectedWindowName]->open();
	_windowMap[_selectedWindowName]->updateInputManager();
}


void Robot::MenuScene::update()
{
	for (auto & window : _windowMap)
	{
		window.second->update();
	}
}


void Robot::MenuScene::draw() const
{
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
