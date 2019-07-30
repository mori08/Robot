#include "MoveMonitorState.h"
#include "StayMonitorState.h"
#include "TargetMonitorState.h"


namespace
{
	const double SPEED                 = 0.8; // ë¨Ç≥
	const double CHANGE_STATE_DISTANCE = 2.4; // èÛë‘ÇïœçXÇ∑ÇÈñ⁄ìIínÇ∆ÇÃãóó£
}


Robot::MoveMonitorState::MoveMonitorState()
{
	_goal.x = Random(0, StageData::WIDTH *StageData::SIZE);
	_goal.y = Random(0, StageData::HEIGHT*StageData::SIZE);
}


void Robot::MoveMonitorState::getMoveVec(Vec2 & monitorPos)
{
	monitorPos += SPEED * (_goal - monitorPos).normalize();
}


void Robot::MoveMonitorState::changeState(PatrolTeamEnemy & patrolTeam)
{
	if ((patrolTeam.getMonitorPos() - GameManager::Instance().getPlayerPos()).length() < RADIUS)
	{
		patrolTeam.changeMonitorState(std::make_unique<TargetMonitorState>());
		patrolTeam.setPoliceChasing(true);
		return;
	}

	if ((patrolTeam.getMonitorPos() - _goal).length() < CHANGE_STATE_DISTANCE)
	{
		patrolTeam.changeMonitorState(std::make_unique<StayMonitorState>());
	}
}
