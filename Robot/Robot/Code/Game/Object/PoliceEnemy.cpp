#include "PoliceEnemy.h"
#include "../../MyColor.h"


namespace
{
	const double RETURN_SPEED = 0.2; // ����ɕς��鑬��
	const double CHASE_SPEED  = 2.4; // �v���C���[��ǂ������鑬��

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
	color.a = 10*_frameCount % 0x80 + 0x80;
	
	Circle(_pos, RADIUS).drawShadow(Vec2::Zero, SHADOW_BLUR_RADIUS, SHADOW_SPREAD, color);
}


Vec2 Robot::PoliceEnemy::getMoveVec()
{
	// �v���C���[��ǐ�
	if (_isChasing)
	{
		return CHASE_SPEED*GameManager::Instance().getPath(_pos, GameManager::Instance().getPlayerPos());
	}

	// �X�^�[�g�ɖ߂�
	return RETURN_SPEED*GameManager::Instance().getPath(_pos, _startPos);
}
