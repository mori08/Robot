#include "FlashEnemy.h"


namespace 
{
	const double SLOW_SPEED = 0.1; // �������łȂ��Ƃ��̑���
	const double SPEED = 1.3;      // ����

	const int FLASH_FRAMECOUNT    = 60;  // �����̃t���[����
	const int CHASE_FRAMECOUNT    = 240; // �ǐՂ̃t���[����
	const int MIN_WAIT_FRAMECOUNT = 300; // ��~�̍ŏ��t���[����
	const int MAX_WAIT_FRAMECOUNT = 900; // ��~�̍ő�t���[����

	const double RADIUS = 30; // ���̔��a

	const double SHADOW_BLUR_RADIUS = 20.0; // �e�̂ڂ����̑傫��
	const double SHADOW_SPREAD      = 20.0; // �e�̍L�����
}


Robot::FlashEnemy::FlashEnemy(const Vec2 & pos)
	: EnemyBase(pos)
{
	_goalPos = pos;
	_changeMoveFramecount = -Random(MIN_WAIT_FRAMECOUNT, MAX_WAIT_FRAMECOUNT);
}


Vec2 Robot::FlashEnemy::getMoveVec(GameManager & gameManager)
{
	++_changeMoveFramecount;

	if (_changeMoveFramecount > CHASE_FRAMECOUNT)
	{
		_changeMoveFramecount = -Random(MIN_WAIT_FRAMECOUNT, MAX_WAIT_FRAMECOUNT);
		_goalPos = RandomVec2(StageData::SIZE*StageData::WIDTH, StageData::SIZE*StageData::HEIGHT);
	}
	
	if (_changeMoveFramecount < FLASH_FRAMECOUNT)
	{
		return SLOW_SPEED*gameManager.getPath(_pos, _goalPos);
	}

	return SPEED*gameManager.getPath(_pos, gameManager.getPlayerPos());
}


void Robot::FlashEnemy::drawLight() const
{
	if (_changeMoveFramecount < 0)
	{
		return;
	}

	Circle(_pos, RADIUS).drawShadow(Vec2::Zero, SHADOW_BLUR_RADIUS, SHADOW_SPREAD, Palette::MyWhite);
}
