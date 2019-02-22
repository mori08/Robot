#include "GiantEnemy.h"


namespace
{
	const int  TEXTURE_CHANGE_SPAN = 8; // 画像を変更する間隔のフレーム数
	const Size TEXTURE_SIZE(180, 180);    // 画像の大きさ

	const double GAMEOVER_DISTANCE = 90.0; // ゲームオーバー判定が行われる距離

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


void Robot::GiantEnemy::update(GameManager & gameManager)
{
	++_frameCount;
	if (_frameCount % TEXTURE_CHANGE_SPAN == 0)
	{
		_texturePos.x++;
	}

	moveObject(gameManager, getMoveVec(gameManager));

	if ((_pos - gameManager.getPlayerPos()).length() < GAMEOVER_DISTANCE)
	{
		gameManager.gameOver();
	}
}


void Robot::GiantEnemy::draw() const
{
	TextureAsset(L"GiantEnemy")(_texturePos*TEXTURE_SIZE, TEXTURE_SIZE).drawAt(_pos);
}


Vec2 Robot::GiantEnemy::getMoveVec(GameManager & gameManager)
{
	Vec2 moveVec = gameManager.getPath(_pos, _goalPos);
	if (moveVec.length() < MIN_VEC_LENGTH)
	{
		_goalPos = RandomVec2(StageData::SIZE*StageData::WIDTH, StageData::SIZE*StageData::HEIGHT);
		return Vec2::Zero;
	}
	return SPEED*moveVec;
}
