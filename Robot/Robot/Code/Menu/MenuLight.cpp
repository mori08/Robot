#include "MenuLight.h"
#include "../MyColor.h"
#include "../SaveData/SaveDataManager.h"


namespace
{
	const double MIN_RADIUS = 10;         // ”¼Œa‚ÌÅ¬’l
	const double MAX_RADIUS = 50;         // ”¼Œa‚ÌÅ‘å’l
	const double SPEED_RATE = 1 / 4000.0; // ”¼Œa‚É‘Î‚µ‚Ä‚Ì‘¬‚³
	const int    ALPHA_RATE = 4;          // ”¼Œa‚É‘Î‚µ‚Ä‚ÌƒAƒ‹ƒtƒ@’l

	const double SHADOW_BLUR_RADIUS = 20.0; // ‰e‚Ì‚Ú‚©‚µ‚Ì‘å‚«‚³
	const double SHADOW_SPREAD      = 20.0; // ‰e‚ÌL‚ª‚è‚©‚½

	const int ALPHA_SPPED = 10;
}


Robot::MenuLight::MenuLight(double x, double r)
	: _region(x, Window::Height() + r + SHADOW_BLUR_RADIUS, r)
	, _speed (r*r*SPEED_RATE)
	, _alpha ((int)r*ALPHA_RATE)
{

}

bool Robot::MenuLight::operator<(const MenuLight & light) const
{
	return _region.r < light._region.r;
}


const Robot::MenuLight Robot::MenuLight::get()
{
	double x = Random(0.0, 1.0*Window::Width());
	double r = Random(MIN_RADIUS, MAX_RADIUS);

	return Robot::MenuLight(x, r);
}


void Robot::MenuLight::update()
{
	if (SaveDataManager::Instance().getFlag(L"Stage9"))
	{
		_alpha -= 1 / Random(1, ALPHA_SPPED);
	}
	else
	{
		_region.y -= _speed;
	}
}


void Robot::MenuLight::draw() const
{
	_region.drawShadow(Vec2::Zero, SHADOW_BLUR_RADIUS, SHADOW_SPREAD, Color(Palette::MyWhite, _alpha));
}


bool Robot::MenuLight::isEraseAble() const
{
	return _region.y + _region.r + SHADOW_BLUR_RADIUS < 0 || _alpha < 0;
}
