#include "MonitorState.h"


namespace
{
	const Color LIGHT_COLOR(Palette::MyWhite, 200); // ���̐F

	const double SHADOW_BLUR_RADIUS = 40.0; // �e�̂ڂ����̑傫��
	const double SHADOW_SPREAD      = 40.0; // �e�̍L�����
}


void Robot::MonitorState::drawLight(const Vec2 & monitorPos) const
{
	Circle(monitorPos, RADIUS).drawShadow(Vec2::Zero, SHADOW_BLUR_RADIUS, SHADOW_SPREAD, LIGHT_COLOR);
}