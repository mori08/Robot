#include "SelectedState.h"


void Robot::SelectedState::update(MenuWindowBase & window)
{
	window.updateSelectedWindowButton();
	window.setBoardAlpha(MenuWindowBase::BOARD_ALPHA);
}


void Robot::SelectedState::draw(const MenuWindowBase & window) const
{
	window.drawButtonAndLight();
}
