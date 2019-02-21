#include "GameLight.h"


namespace
{
	const double RATE = 0.9;  // �ړ��̊���
	const double RADIUS = 50; // ���̔��a

	const double SHADOW_BLUR_RADIUS = 20.0; // �e�̂ڂ����̑傫��
	const double SHADOW_SPREAD      = 20.0;  // �e�̍L�����
}


void Robot::GameLight::update()
{
	_pos = RATE*_pos + (1 - RATE)*Mouse::PosF();
}


void Robot::GameLight::draw() const
{
	Circle(_pos, RADIUS).drawShadow(Vec2::Zero, SHADOW_BLUR_RADIUS, SHADOW_SPREAD, Palette::MyWhite);
}
