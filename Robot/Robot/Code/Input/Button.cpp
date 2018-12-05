#include "Button.h"


Robot::Button::Button(const String & key, const Rect & region)
	: _key(key)
	, _region(region)
{
	_adjacentButtonList[UP]    = nullptr;
	_adjacentButtonList[DOWN]  = nullptr;
	_adjacentButtonList[LEFT]  = nullptr;
	_adjacentButtonList[RIGHT] = nullptr;
}
