#include "OpeningState.h"
#include "SelectedState.h"


namespace
{
	const int    DRAW_BUTTON_SPAN = 3;
	const double RATE = 0.8;
}


Robot::OpeningState::OpeningState(size_t numOfButton, const Vec2 & offset)
	: _frameCount(0)
	, _offsetList(numOfButton, offset)
	, _alphaList(numOfButton, 0)
{

}


void Robot::OpeningState::update(MenuWindowBase & window)
{
	++_frameCount;

	for (size_t i = 0; i < Min(_frameCount / DRAW_BUTTON_SPAN, window.numOfButton()); ++i)
	{
		_offsetList[i] *= RATE;
		_alphaList[i]  = RATE * _alphaList[i] + (1 - RATE)*1.0;
	}

	window.setColor(MenuWindowBase::NON_SELECTED_COLOR, _frameCount / DRAW_BUTTON_SPAN);

	if (_frameCount / DRAW_BUTTON_SPAN > window.numOfButton())
	{
		window.changeState(std::make_unique<SelectedState>());
	}
}


void Robot::OpeningState::draw(const MenuWindowBase & window) const
{
	window.drawButtonAndLight(_offsetList, _alphaList);
}
