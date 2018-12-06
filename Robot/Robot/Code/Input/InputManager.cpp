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


void Robot::InputManager::changeState()
{
	Optional<String> nextStateKey = _inputState->changeState(_inputState);

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
