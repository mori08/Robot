#include "PoliceEnemy.h"
#include "../../MyColor.h"


namespace
{
	const double RETURN_SPEED = 0.2; // ê‚É•Ï‚¦‚é‘¬‚³
	const double CHASE_SPEED  = 2.4; // ƒvƒŒƒCƒ„[‚ğ’Ç‚¢‚©‚¯‚é‘¬‚³

	const double RADIUS = 30; // Œõ‚Ì”¼Œa
	const double SHADOW_BLUR_RADIUS = 20.0; // ‰e‚Ì‚Ú‚©‚µ‚Ì‘å‚«‚³
	const double SHADOW_SPREAD      = 20.0; // ‰e‚ÌL‚ª‚è•û
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


Vec2 Robot::PoliceEnemy::getMoveVec(GameManager & gameManager)
{
	if (_isChasing)
	{
		return CHASE_SPEED*gameManager.getPath(_pos, gameManager.getPlayerPos());
	}

	return RETURN_SPEED*gameManager.getPath(_pos, _startPos);
}
