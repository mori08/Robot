#include "SelectedState.h"


void Robot::SelectedState::update(MenuWindowBase & window)
{
	window.updateSelectedWindowButton();
}


void Robot::SelectedState::draw(const MenuWindowBase & window) const
{
	window.drawButtonAndLight();
}
