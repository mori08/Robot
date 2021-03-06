#include "MonitorState.h"
#include "../../../MyColor.h"


namespace
{
	const Color LIGHT_COLOR(Robot::Palette::MyWhite, 200); // 光の色

	const double SHADOW_BLUR_RADIUS = 30.0; // 影のぼかしの大きさ
	const double SHADOW_SPREAD      = 30.0; // 影の広がり方
}


void Robot::MonitorState::drawLight(const Vec2 & monitorPos) const
{
	Circle(monitorPos, RADIUS).drawShadow(Vec2::Zero, SHADOW_BLUR_RADIUS, SHADOW_SPREAD, LIGHT_COLOR);
}