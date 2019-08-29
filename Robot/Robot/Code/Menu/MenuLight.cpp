#include "MenuLight.h"
#include "../MyColor.h"


namespace
{
	const double MIN_RADIUS = 10;         // ���a�̍ŏ��l
	const double MAX_RADIUS = 50;         // ���a�̍ő�l
	const double SPEED_RATE = 1 / 4000.0; // ���a�ɑ΂��Ă̑���
	const int    ALPHA_RATE = 4;          // ���a�ɑ΂��ẴA���t�@�l

	const double SHADOW_BLUR_RADIUS = 20.0; // �e�̂ڂ����̑傫��
	const double SHADOW_SPREAD      = 20.0; // �e�̍L���肩��
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
	_region.y -= _speed;
}


void Robot::MenuLight::draw() const
{
	_region.drawShadow(Vec2::Zero, SHADOW_BLUR_RADIUS, SHADOW_SPREAD, Color(Palette::MyWhite, _alpha));
}


bool Robot::MenuLight::isEraseAble() const
{
	return _region.y + _region.r + SHADOW_BLUR_RADIUS < 0;
}
