#include "OpenedState.h"


void Robot::OpenedState::update(MenuWindowBase & window)
{
	window.setColor(MenuWindowBase::SHOWED_COLOR);
}


void Robot::OpenedState::draw(const MenuWindowBase & window) const
{
	window.drawButtonAndLight();
}
