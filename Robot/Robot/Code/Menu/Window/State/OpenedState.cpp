#include "OpenedState.h"


void Robot::OpenedState::update(MenuWindowBase & window)
{
	window.setColor(MenuWindowBase::NON_SELECTED_COLOR);
	window.setBoardAlpha(0.5);
}


void Robot::OpenedState::draw(const MenuWindowBase & window) const
{
	window.drawButtonAndLight();
}
