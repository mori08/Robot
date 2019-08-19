#include "FlashEnemy.h"
#include "../../MyColor.h"


namespace 
{
	const double SLOW_SPEED = 0.1; // 発光時でないときの速さ
	const double SPEED = 1.3;      // 速さ

	const int FLASH_FRAMECOUNT    = 60;  // 発光のフレーム数
	const int CHASE_FRAMECOUNT    = 240; // 追跡のフレーム数
	const int MIN_WAIT_FRAMECOUNT = 300; // 停止の最小フレーム数
	const int MAX_WAIT_FRAMECOUNT = 900; // 停止の最大フレーム数

	const double RADIUS = 30; // 光の半径

	const double SHADOW_BLUR_RADIUS = 20.0; // 影のぼかしの大きさ
	const double SHADOW_SPREAD      = 20.0; // 影の広がり方
}


Robot::FlashEnemy::FlashEnemy(const Vec2 & pos)
	: EnemyBase(pos)
{
	_goalPos = pos;
	_changeMoveFramecount = -Random(MIN_WAIT_FRAMECOUNT, MAX_WAIT_FRAMECOUNT);
}


Vec2 Robot::FlashEnemy::getMoveVec()
{
	++_changeMoveFramecount;

	if (_changeMoveFramecount > CHASE_FRAMECOUNT)
	{
		_changeMoveFramecount = -Random(MIN_WAIT_FRAMECOUNT, MAX_WAIT_FRAMECOUNT);
		_goalPos = RandomVec2(StageData::SIZE*StageData::WIDTH, StageData::SIZE*StageData::HEIGHT);
	}
	
	// 一定時間 低速でランダムな座標に移動
	if (_changeMoveFramecount < FLASH_FRAMECOUNT)
	{
		return SLOW_SPEED*GameManager::Instance().getPath(_pos, _goalPos);
	}

	// プレイヤーを追跡
	return SPEED*GameManager::Instance().getPath(_pos, GameManager::Instance().getPlayerPos());
}


void Robot::FlashEnemy::drawLight() const
{
	if (_changeMoveFramecount < 0)
	{
		return;
	}

	// プレイヤーを追跡中は光る
	Circle(_pos, RADIUS).drawShadow(Vec2::Zero, SHADOW_BLUR_RADIUS, SHADOW_SPREAD, Palette::MyWhite);
}
