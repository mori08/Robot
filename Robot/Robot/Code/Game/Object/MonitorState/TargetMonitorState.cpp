#include "TargetMonitorState.h"


namespace
{
	const double SPEED = 5.0;
}


void Robot::TargetMonitorState::getMoveVec(Vec2 & monitorPos)
{
	monitorPos += SPEED * (GameManager::Instance().getPlayerPos() - monitorPos).normalize();
}


void Robot::TargetMonitorState::changeState(PatrolTeamEnemy & patrolTeam)
{
	if ((GameManager::Instance().getPlayerPos() - patrolTeam.getMonitorPos()).length() < SPEED)
	{
		// ChaseMonitorState‚Ö
	}
}
