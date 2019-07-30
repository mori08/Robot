#include "ChaseMonitorState.h"
#include "StayMonitorState.h"


namespace
{
	const double SPEED = 0.6; // ‘¬‚³
}


void Robot::ChaseMonitorState::getMoveVec(Vec2 & monitorPos)
{
	monitorPos += SPEED*(GameManager::Instance().getPlayerPos() - monitorPos).normalize();
}


void Robot::ChaseMonitorState::changeState(PatrolTeamEnemy & patrolTeam)
{
	if ((patrolTeam.getMonitorPos() - GameManager::Instance().getPlayerPos()).length() > RADIUS)
	{
		patrolTeam.changeMonitorState(std::make_unique<StayMonitorState>());
	}
}
