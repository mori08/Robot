#include "PatrolTeamEnemy.h"
#include "MonitorState\StayMonitorState.h"


namespace
{
	const std::vector<Point> POLICE_POS // PoliceEnemyÇê∂ê¨Ç∑ÇÈç¿ïW
	{
		Point(0                          , 0),
		Point(Robot::StageData::WIDTH - 1, 0),
		Point(Robot::StageData::WIDTH - 1, Robot::StageData::HEIGHT - 1),
		Point(0                          , Robot::StageData::HEIGHT - 1)
	};

	const double MONITOR_SPEED = 0.2;
}


Robot::PatrolTeamEnemy::PatrolTeamEnemy(const Vec2 & pos)
	: GameObject(pos)
	, _monitorPos(pos)
	, _monitorState(std::make_unique<StayMonitorState>())
{
	for (auto & p : POLICE_POS)
	{
		_policeList.emplace_back(StageData::centerPosOfCell(p));
	}
}


void Robot::PatrolTeamEnemy::setPoliceChasing(bool isChasing)
{
	for (auto & police : _policeList)
	{
		police.setChase(isChasing);
	}
}


void Robot::PatrolTeamEnemy::update()
{
	_monitorState->changeState(*this);
	_monitorState->getMoveVec(_monitorPos);

	for (auto & police : _policeList)
	{
		police.update();
	}
}


void Robot::PatrolTeamEnemy::draw() const
{
	for (const auto & police : _policeList)
	{
		police.draw();
	}
}


void Robot::PatrolTeamEnemy::drawLight() const
{
	_monitorState->drawLight(_monitorPos);

	for (const auto & police : _policeList)
	{
		police.drawLight();
	}
}
