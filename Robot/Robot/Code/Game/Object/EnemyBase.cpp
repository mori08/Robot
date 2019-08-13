#include "EnemyBase.h"


namespace
{
	const int  TEXTURE_CHANGE_SPAN = 4; // �摜��ύX����Ԋu�̃t���[����
	const Size TEXTURE_SIZE(40, 40);    // �摜�̑傫��

	const double GAMEOVER_DISTANCE = 15.0; // �Q�[���I�[�o�[���肪�s���鋗��
}


Robot::EnemyBase::EnemyBase(const Vec2 & pos)
	: GameObject(pos)
	, _frameCount(0)
	, _texturePos(0, 0)
{
}


void Robot::EnemyBase::update(GameManager & gameManager)
{
	++_frameCount;
	if (_frameCount % TEXTURE_CHANGE_SPAN == 0) 
	{
		_texturePos.x++;
	}

	moveObject(gameManager, getMoveVec(gameManager));

	if ((_pos - gameManager.getPlayerPos()).length() < GAMEOVER_DISTANCE)
	{
		gameOver(gameManager);
	}
}


void Robot::EnemyBase::draw() const
{
	TextureAsset(L"Enemy")(_texturePos*TEXTURE_SIZE, TEXTURE_SIZE).drawAt(_pos);
}
