#include "FriendEnemy.h"
#include "../../MyColor.h"


namespace
{
	const int SPEED_UP_SPAN  = 180; // �������グ��t���[�����̊Ԋu
	const int SHAKE_UP_SPAN  = 480; // ��ʂ̗h����グ��t���[�����̊Ԋu
	const int DRAW_TEXT_SPAN = 120;  // �e�L�X�g��\������t���[�����̊Ԋu
	const Point  DRAW_TEXT_POS(320, 440); // �e�L�X�g��\��������W

	const double SPEEDUP = 0.1;
	const int    SHAKEUP = 1;
}


Robot::FriendEnemy::FriendEnemy(const Vec2 & pos)
	: EnemyBase(pos)
	, _speed(0)
	, _shake(0)
{
}


void Robot::FriendEnemy::drawLight() const
{
	for (int i = 0; i < StageData::N; ++i)
	{
		Point randPos = Point(Random(-_shake, _shake), Random(-_shake, _shake));
		Rect(StageData::SIZE*StageData::intToPoint(i) + randPos, StageData::SIZE).draw(Palette::MyWhite);
	}

	size_t drawTextLength = _frameCount / DRAW_TEXT_SPAN;
	String text = L"�l�̃R�R����\n�������Ȃ񂩂���Ȃ�";
	FontAsset(L"20")(text.substr(0, drawTextLength)).drawAt(DRAW_TEXT_POS, Palette::MyBlack);
}


Vec2 Robot::FriendEnemy::getMoveVec()
{
	// �X�s�[�h���グ�Ă���
	if (_frameCount%SPEED_UP_SPAN == 0)
	{
		_speed += SPEEDUP;
	}

	if (_frameCount%SHAKE_UP_SPAN == 0)
	{
		_shake += SHAKEUP;
	}

	// �v���C���[��ǐ�
	return _speed*GameManager::Instance().getPath(_pos, GameManager::Instance().getPlayerPos());
}
