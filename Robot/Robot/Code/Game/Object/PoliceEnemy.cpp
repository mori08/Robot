#include "PoliceEnemy.h"


namespace
{
	const double RETURN_SPEED = 0.2; // ����ɕς��鑬��
	const double CHASE_SPEED  = 1.0; // �v���C���[��ǂ������鑬��

	const double RADIUS = 30; // ���̔��a
	const double SHADOW_BLUR_RADIUS = 20.0; // �e�̂ڂ����̑傫��
	const double SHADOW_SPREAD      = 20.0; // �e�̍L�����
}


Robot::PoliceEnemy::PoliceEnemy(const Vec2 & pos)
	: EnemyBase(pos)
	, _isChasing(false)
	, _startPos(pos)
{
}


void Robot::PoliceEnemy::drawLight() const
{
	if (!_isChasing) { return; }

	Color color = Palette::MyWhite;
	color.a = _frameCount;
	
	Circle(_pos, RADIUS).drawShadow(Vec2::Zero, SHADOW_BLUR_RADIUS, SHADOW_SPREAD, Palette::MyWhite);
}


Vec2 Robot::PoliceEnemy::getMoveVec(GameManager & gameManager)
{
	if (_isChasing)
	{
		return CHASE_SPEED*gameManager.getPath(_pos, gameManager.getPlayerPos());
	}

	return RETURN_SPEED*gameManager.getPath(_pos, _startPos);
}
