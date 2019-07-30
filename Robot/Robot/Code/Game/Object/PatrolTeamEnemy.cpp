#include "PatrolTeamEnemy.h"
#include "MonitorState\StayMonitorState.h"


namespace
{
	const std::vector<Point> POLICE_POS // PoliceEnemyÇê∂ê¨Ç∑ÇÈç¿ïW
	{

	};

	const double MONITOR_SPEED = 0.2;
}


Robot::PatrolTeamEnemy::PatrolTeamEnemy(const Vec2 & pos)
	: GameObject(pos)
	, _monitorPos(pos)
	, _monitorState(std::make_unique<StayMonitorState>())
{
}


void Robot::PatrolTeamEnemy::update(GameManager & gameManager)
{
	_monitorState->changeState(*this);
	_monitorState->getMoveVec(_monitorPos);
}


void Robot::PatrolTeamEnemy::draw() const
{
}


void Robot::PatrolTeamEnemy::drawLight() const
{
	_monitorState->drawLight(_monitorPos);
}
