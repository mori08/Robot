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
	_windowList[L"Main"] = std::make_shared<MainWindow>();
	_windowList[L"Main"]->setClickedProcessing(L"Title", std::make_unique<Processing>([this]() { changeScene(L"TitleScene"); }));
	_windowList[L"Main"]->setClickedProcessing(L"Stage", std::make_unique<Processing>([this]() { openWindow(L"Stage"); }));

	_windowList[L"Stage"] = std::make_shared<StageWindow>();
	for (int i = 0; i < 10; ++i)
	{
		String stageName = L"Stage" + ToString(i);
		_windowList[L"Stage"]->setClickedProcessing(stageName, std::make_unique<Processing>(
			[this,stageName]() 
			{
				m_data->sceneInfo = stageName;
				changeScene(L"LoadGameScene");
			}
		));
	}

	_windowList[L"Stage"]->setClickedProcessing(L"TitleButton", std::make_unique<Processing>([this]() { changeScene(L"TitleScene"); }));

	_windowStack.emplace_back(_windowList[L"Main"]);
	(*_windowStack.rbegin())->updateInputManager();
}


void Robot::MenuScene::update()
{
	auto itr = _windowStack.rbegin();
	(*itr)->update();
	
	for (++itr; itr != _windowStack.rend(); ++itr)
	{
		(*itr)->updateNonSelectedWindow();
	}
}


void Robot::MenuScene::draw() const
{
	for (const auto & window : _windowStack)
	{
		window->draw();
	}
}


void Robot::MenuScene::openWindow(const String & windowName)
{
	if (_windowList.find(windowName) == _windowList.end()) { return; }

	_windowStack.emplace_back(_windowList[windowName]);
	(*_windowStack.rbegin())->updateInputManager();
}
