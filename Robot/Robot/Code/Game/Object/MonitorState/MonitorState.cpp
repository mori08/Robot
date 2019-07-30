#include "MonitorState.h"


namespace
{
	const Color LIGHT_COLOR(Palette::MyWhite, 200); // Œõ‚ÌF

	const double SHADOW_BLUR_RADIUS = 40.0; // ‰e‚Ì‚Ú‚©‚µ‚Ì‘å‚«‚³
	const double SHADOW_SPREAD      = 40.0; // ‰e‚ÌL‚ª‚è•û
}


void Robot::MonitorState::drawLight(const Vec2 & monitorPos) const
{
	Circle(monitorPos, RADIUS).drawShadow(Vec2::Zero, SHADOW_BLUR_RADIUS, SHADOW_SPREAD, LIGHT_COLOR);
}