#include "SelectedState.h"


void Robot::SelectedState::update(MenuWindowBase & window)
{
	window.updateSelectedWindowButton();
	window.setBoardAlpha(0.5);
}


void Robot::SelectedState::draw(const MenuWindowBase & window) const
{
	window.drawButtonAndLight();
}
