#include "GiantEnemy.h"
#include "../State/GameOverState.h"


namespace
{
	const int  TEXTURE_CHANGE_SPAN = 8; // �摜��ύX����Ԋu�̃t���[����
	const Size TEXTURE_SIZE(180, 180);    // �摜�̑傫��

	const double GAMEOVER_DISTANCE = 90.0; // �Q�[���I�[�o�[���肪�s���鋗��

	const double MIN_VEC_LENGTH = 0.5;
	const double SPEED = 0.3;
}


Robot::GiantEnemy::GiantEnemy(const Vec2 & pos)
	: EnemyBase(pos)
	, _frameCount(0)
	, _texturePos(0,0)
	, _goalPos(pos)
{

}


void Robot::GiantEnemy::update()
{
	++_frameCount;
	if (_frameCount % TEXTURE_CHANGE_SPAN == 0)
	{
		_texturePos.x++;
	}

	moveObject(getMoveVec());

	if ((_pos - GameManager::Instance().getPlayerPos()).length() < GAMEOVER_DISTANCE)
	{
		GameManager::Instance().changeGameState(std::make_unique<GameOverState>());
	}
}


void Robot::GiantEnemy::draw() const
{
	TextureAsset(L"GiantEnemy")(_texturePos*TEXTURE_SIZE, TEXTURE_SIZE).drawAt(_pos);
}


Vec2 Robot::GiantEnemy::getMoveVec()
{
	// �����_���ȍ��W�ֈړ�
	Vec2 moveVec = GameManager::Instance().getPath(_pos, _goalPos);
	if (moveVec.length() < MIN_VEC_LENGTH)
	{
		_goalPos = RandomVec2(StageData::SIZE*StageData::WIDTH, StageData::SIZE*StageData::HEIGHT);
		return Vec2::Zero;
	}
	return SPEED*moveVec;
}
