#include "MenuScene.h"
#include "Window\MainWindow.h"


namespace
{
	using Processing = std::function<void()>;
}


Robot::MenuScene::MenuScene()
{
	_windowList[L"Main"] = std::make_shared<MainWindow>();
	_windowList[L"Main"]->setClickedProcessing(L"Title", std::make_unique<Processing>([this]() { changeScene(L"TitleScene"); }));

	_windowStack.emplace_back(_windowList[L"Main"]);
	(*_windowStack.rbegin())->updateInputManager();
}


void Robot::MenuScene::update()
{
	(*_windowStack.rbegin())->update();
}


void Robot::MenuScene::draw() const
{
	for (const auto & window : _windowStack)
	{
		window->draw();
	}
}
