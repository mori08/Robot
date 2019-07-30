#include "TargetMonitorState.h"
#include "ChaseMonitorState.h"


namespace
{
	const double SPEED = 5.0;
	const double LENGTH = 2 * SPEED;
}


void Robot::TargetMonitorState::getMoveVec(Vec2 & monitorPos)
{
	monitorPos += SPEED * (GameManager::Instance().getPlayerPos() - monitorPos).normalize();
}


void Robot::TargetMonitorState::changeState(PatrolTeamEnemy & patrolTeam)
{
	if ((GameManager::Instance().getPlayerPos() - patrolTeam.getMonitorPos()).length() < LENGTH)
	{
		patrolTeam.changeMonitorState(std::make_unique<ChaseMonitorState>());
	}
}
