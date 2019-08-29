#include "MenuManager.h"
#include "Window\MainWindow.h"
#include "Window\StageWindow.h"
#include "Window\DiaryWindow.h"


Robot::MenuManager::MenuManager()
{
	_windowMap[L"Main"]  = std::make_unique<MainWindow> ();
	_windowMap[L"Stage"] = std::make_unique<StageWindow>();
	_windowMap[L"Diary"] = std::make_unique<DiaryWindow>();

	_selectedWindowName = L"Main";

	_windowMap[_selectedWindowName]->open();
}


void Robot::MenuManager::update()
{
	for (auto && window : _windowMap)
	{
		window.second->update();
	}
}


void Robot::MenuManager::draw() const
{
	for (const auto & window : _windowMap)
	{
		window.second->draw();
	}
}


void Robot::MenuManager::load()
{
	_isChangeAbleScene = false;
	for (auto & window : _windowMap)
	{
		window.second->load();
	}
	_windowMap[_selectedWindowName]->updateInputManager();
}


bool Robot::MenuManager::isChangeAbleScene(String & sceneName, String & sceneInfo) const
{
	sceneName = _sceneName.first;
	sceneInfo = _sceneName.second;
	return _isChangeAbleScene;
}


void Robot::MenuManager::openWindow(const String & windowName)
{
	if (_windowMap.find(windowName) == _windowMap.end()) { return; }

	_windowMap[_selectedWindowName]->nonSelect();
	_windowMap[windowName]->open();
	_windowMap[windowName]->updateInputManager();
	_selectedWindowName = windowName;
}


void Robot::MenuManager::closeWindow(const String & windowName)
{
	if (_windowMap.find(windowName) == _windowMap.end()) { return; }

	_windowMap[_selectedWindowName]->close();
	_windowMap[windowName]->select();
	_windowMap[windowName]->updateInputManager();
	_selectedWindowName = windowName;
}


void Robot::MenuManager::setSceneName(const String & sceneName, const String & sceneInfo)
{
	_isChangeAbleScene = true;
	_sceneName         = { sceneName,sceneInfo };
}
