#include "MonitorState.h"


namespace
{
	const Color LIGHT_COLOR(Palette::MyWhite, 128); // ���̐F
}


void Robot::MonitorState::drawLight(const Vec2 & monitorPos) const
{
	Circle(monitorPos, RADIUS).draw(LIGHT_COLOR);
}