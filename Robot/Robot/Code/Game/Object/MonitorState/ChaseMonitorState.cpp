#include "ChaseMonitorState.h"
#include "StayMonitorState.h"


namespace
{
	const double SPEED = 0.4; // ‘¬‚³
}


void Robot::ChaseMonitorState::getMoveVec(Vec2 & monitorPos)
{
	monitorPos += SPEED*(GameManager::Instance().getPlayerPos() - monitorPos).normalize();
}


void Robot::ChaseMonitorState::changeState(PatrolTeamEnemy & patrolTeam)
{
	if ((patrolTeam.getMonitorPos() - GameManager::Instance().getPlayerPos()).length() > CHASE_DISTANCE)
	{
		patrolTeam.changeMonitorState(std::make_unique<StayMonitorState>());
		patrolTeam.setPoliceChasing(false);
	}
}
