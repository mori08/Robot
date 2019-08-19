#include "PoliceEnemy.h"
#include "../../MyColor.h"


namespace
{
	const double RETURN_SPEED = 0.2; // 持場に変える速さ
	const double CHASE_SPEED  = 2.4; // プレイヤーを追いかける速さ

	const double RADIUS = 30; // 光の半径
	const double SHADOW_BLUR_RADIUS = 20.0; // 影のぼかしの大きさ
	const double SHADOW_SPREAD      = 20.0; // 影の広がり方
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
	// プレイヤーを追跡
	if (_isChasing)
	{
		return CHASE_SPEED*GameManager::Instance().getPath(_pos, GameManager::Instance().getPlayerPos());
	}

	// スタートに戻る
	return RETURN_SPEED*GameManager::Instance().getPath(_pos, _startPos);
}
