#include "ClosingState.h"
#include "ClosedState.h"


namespace
{
	const double RATE = 0.8;
	const int    CHANGE_STATE_FRAME_COUNT = 30;
}


Robot::ClosingState::ClosingState(const Vec2 & offset)
	: _frameCount(0)
	, _offset(Vec2::Zero)
	, MAX_OFFSET(offset)
{

}


void Robot::ClosingState::update(MenuWindowBase & window)
{
	++_frameCount;

	_offset = RATE*_offset + (1 - RATE)*MAX_OFFSET;

	window.setColor(MenuWindowBase::NON_SHOWED_COLOR);

	if (_frameCount > CHANGE_STATE_FRAME_COUNT)
	{
		window.changeState(std::make_unique<ClosedState>());
	}
}


void Robot::ClosingState::draw(const MenuWindowBase & window) const
{
	window.drawButtonAndLight(_offset);
}
