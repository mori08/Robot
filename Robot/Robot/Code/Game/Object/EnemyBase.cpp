#include "EnemyBase.h"
#include "../State/GameOverState.h"


namespace
{
	const int  TEXTURE_CHANGE_SPAN = 4; // 画像を変更する間隔のフレーム数
	const Size TEXTURE_SIZE(40, 40);    // 画像の大きさ

	const double GAMEOVER_DISTANCE = 15.0; // ゲームオーバー判定が行われる距離
}


Robot::EnemyBase::EnemyBase(const Vec2 & pos)
	: GameObject(pos)
	, _frameCount(0)
	, _texturePos(0, 0)
{
}


void Robot::EnemyBase::update()
{
	++_frameCount;
	if (_frameCount % TEXTURE_CHANGE_SPAN == 0) 
	{
		_texturePos.x++;
	}

	moveObject(getMoveVec());

	if ((_pos - GameManager::Instance().getPlayerPos()).length() < GAMEOVER_DISTANCE)
	{
		gameOver();
	}
}


void Robot::EnemyBase::draw() const
{
	TextureAsset(L"Enemy")(_texturePos*TEXTURE_SIZE, TEXTURE_SIZE).drawAt(_pos);
}


void Robot::EnemyBase::gameOver()
{
	GameManager::Instance().changeGameState(std::make_unique<GameOverState>());
}
