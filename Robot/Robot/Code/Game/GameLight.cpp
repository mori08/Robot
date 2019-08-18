#include "GameLight.h"
#include "../MyColor.h"


namespace
{
	const double RATE = 0.9;  // �ړ��̊���
	const double RADIUS = 60; // ���̔��a

	const double SHADOW_BLUR_RADIUS = 40.0; // �e�̂ڂ����̑傫��
	const double SHADOW_SPREAD      = 40.0; // �e�̍L�����
}


void Robot::GameLight::update()
{
	_pos = RATE*_pos + (1 - RATE)*Mouse::PosF();
}


void Robot::GameLight::draw() const
{
	if (_off) { return; }
	Circle(_pos, RADIUS).drawShadow(Vec2::Zero, SHADOW_BLUR_RADIUS, SHADOW_SPREAD, Palette::MyWhite);
}
