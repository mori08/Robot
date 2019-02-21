#include "GameLight.h"


namespace
{
	const double RATE = 0.9;  // ˆÚ“®‚ÌŠ„‡
	const double RADIUS = 60; // Œõ‚Ì”¼Œa

	const double SHADOW_BLUR_RADIUS = 40.0; // ‰e‚Ì‚Ú‚©‚µ‚Ì‘å‚«‚³
	const double SHADOW_SPREAD      = 40.0; // ‰e‚ÌL‚ª‚è•û
}


void Robot::GameLight::update()
{
	_pos = RATE*_pos + (1 - RATE)*Mouse::PosF();
}


void Robot::GameLight::draw() const
{
	Circle(_pos, RADIUS).drawShadow(Vec2::Zero, SHADOW_BLUR_RADIUS, SHADOW_SPREAD, Palette::MyWhite);
}
