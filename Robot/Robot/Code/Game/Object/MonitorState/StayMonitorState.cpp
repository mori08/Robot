#include "StayMonitorState.h"
#include "MoveMonitorState.h"


namespace
{
	const int MIN_STAY_FRAMECOUNT = 60;
	const int MAX_STAY_FRAMECOUNT = 120;
}


Robot::StayMonitorState::StayMonitorState()
{
	_stayFrameCount = Random(MIN_STAY_FRAMECOUNT, MAX_STAY_FRAMECOUNT);
}


void Robot::StayMonitorState::getMoveVec(Vec2 &)
{
	
}


void Robot::StayMonitorState::changeState(PatrolTeamEnemy & patrolTeam)
{
	if (--_stayFrameCount > 0) { return; }

	patrolTeam.changeMonitorState(std::make_unique<MoveMonitorState>());
}
