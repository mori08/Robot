#include "InputManager.h"
#include "KeyInputState.h"
#include "MouseInputState.h"


Robot::InputManager::InputManager()
	: _selectedButton(nullptr)
	, _inputState(std::make_unique<KeyInputState>())
{
	
}


void Robot::InputManager::registerButton(const String & key, const Rect & region)
{
	_buttonList[key] = std::make_shared<Button>(key, region);
}


void Robot::InputManager::setVerticalAdjacentButton(const String & upKey, const String & downKey)
{
#ifdef _DEBUG

	if (_buttonList.find(upKey)   == _buttonList.end()) 
	{
		Println(L"Error > setVerticalAdjacentButtonで存在しないキーが指定されています。");
		return; 
	}
	if (_buttonList.find(downKey) == _buttonList.end()) 
	{
		Println(L"Error > setVerticalAdjacentButtonで存在しないキーが指定されています。");
		return; 
	}
	

#endif // _DEBUG

	ButtonPtr upButton   = _buttonList[upKey];
	ButtonPtr downButton = _buttonList[downKey];

	upButton->  setAdjacentButton(Button::DOWN, downButton);
	downButton->setAdjacentButton(Button::UP  , upButton  );
}


void Robot::InputManager::setHorizontalAdjacentButton(const String & leftKey, const String & rightKey)
{
#ifdef _DEBUG

	if (_buttonList.find(leftKey)  == _buttonList.end())
	{
		Println(L"Error > setHorizontalAdjacentButtonで存在しないキーが指定されています。");
		return; 
	}
	if (_buttonList.find(rightKey) == _buttonList.end()) 
	{
		Println(L"Error > setHorizontalAdjacentButtonで存在しないキーが指定されています。");
		return; 
	}

#endif // _DEBUG

	ButtonPtr leftButton  = _buttonList[leftKey];
	ButtonPtr rightButton = _buttonList[rightKey];

	leftButton-> setAdjacentButton(Button::RIGHT, rightButton);
	rightButton->setAdjacentButton(Button::LEFT , leftButton);
}


void Robot::InputManager::setSelectedButton(const String & key)
{
#ifdef _DEBUG

	if (_buttonList.find(key) == _buttonList.end())
	{
		Println(L"Error > setSelectedButtonで存在しないキーが指定されています。");
		Println(key);
		return;
	}

#endif // _DEBUG

	_selectedButton = _buttonList[key];
}


void Robot::InputManager::changeState()
{
	Optional<String> nextStateKey = _inputState->changeState();

	if (!nextStateKey)
	{
		return;
	}

	if (*nextStateKey == L"KeyInputState")
	{
		_inputState = std::make_unique<KeyInputState>();
	}

	if (*nextStateKey == L"MouseInputState")
	{
		_inputState = std::make_unique<MouseInputState>();
	}
}
