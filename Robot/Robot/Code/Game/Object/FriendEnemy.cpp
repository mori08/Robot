#include "FriendEnemy.h"


namespace
{
	const int SPEED_UP_SPAN  = 180; // 速さを上げるフレーム数の間隔
	const int SHAKE_UP_SPAN  = 480; // 画面の揺れを上げるフレーム数の間隔
	const int DRAW_TEXT_SPAN = 120;  // テキストを表示するフレーム数の間隔
	const Point  DRAW_TEXT_POS(320, 440); // テキストを表示する座標

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
	String text = L"僕のこころは\n未完成なんかじゃない";
	FontAsset(L"20")(text.substr(0, drawTextLength)).drawAt(DRAW_TEXT_POS, Palette::MyBlack);
}


Vec2 Robot::FriendEnemy::getMoveVec(GameManager & gameManager)
{
	if (_frameCount%SPEED_UP_SPAN == 0)
	{
		_speed += SPEEDUP;
	}

	if (_frameCount%SHAKE_UP_SPAN == 0)
	{
		_shake += SHAKEUP;
	}

	return _speed*gameManager.getPath(_pos, gameManager.getPlayerPos());
}
