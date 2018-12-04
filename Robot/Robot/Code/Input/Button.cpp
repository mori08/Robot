#include "Button.h"


Robot::Button::Button(const String & key, const Rect region)
	: _key(key)
	, _region(region)
{
	_adjacentButtonList[UP]    = nullptr;
	_adjacentButtonList[DOWN]  = nullptr;
	_adjacentButtonList[LEFT]  = nullptr;
	_adjacentButtonList[RIGHT] = nullptr;
}


void Robot::Button::setAdjacentButton(int direction, std::shared_ptr<Button> adjacentButton)
{
#ifdef _DEBUG
	if (direction < 0 || direction > ADJACENT_BUTTON_SIZE)
	{
		Println(L"Error > setAdjuacnetButtonÇ≈ïsìKêÿÇ»ì¸óÕ : ", direction);
		return;
	}
#endif // _DEBUG

	_adjacentButtonList[direction] = adjacentButton;
}
