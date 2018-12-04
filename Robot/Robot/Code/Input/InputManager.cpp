#include "InputManager.h"


namespace
{
	const int GAMEPAD_ID = 0;
}


void Robot::InputManager::registerButton(const String & key, const Rect & region)
{
	_buttonList[key] = std::make_shared<Button>(key, region);
}

