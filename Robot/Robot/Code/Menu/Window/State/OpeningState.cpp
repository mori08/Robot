#include "OpeningState.h"
#include "SelectedState.h"


namespace
{
	const double RATE = 0.8;
	const int    CHANGE_STATE_FRAME_COUNT = 30;
}


Robot::OpeningState::OpeningState(const Vec2 & offset)
	: _frameCount(0)
	, _offset(offset)
{

}


void Robot::OpeningState::update(MenuWindowBase & window)
{
	++_frameCount;

	_offset *= RATE;

	window.setColor(MenuWindowBase::SELECTED_COLOR);
	window.moveCursol();
	window.setBoardAlpha(MenuWindowBase::BOARD_ALPHA);

	if (_frameCount > CHANGE_STATE_FRAME_COUNT)
	{
		window.changeState(std::make_unique<SelectedState>());
	}
}


void Robot::OpeningState::draw(const MenuWindowBase & window) const
{
	window.drawButtonAndLight(_offset);
}
