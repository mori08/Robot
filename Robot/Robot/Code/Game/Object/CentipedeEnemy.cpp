#include "CentipedeEnemy.h"
#include "../../MyColor.h"


namespace
{
	const size_t LEADER_INDEX  = 0;  // æ“ª‚ÌƒCƒ“ƒfƒbƒNƒX
	const size_t BODY_DISTANCE = 40; // ‘Ì‚Ì•”•i‚ª•Û‚Â‹——£

	const double RADIUS             = 30.0; // Œõ‚Ì”¼Œa
	const double SHADOW_BLUR_RADIUS = 10.0; // ‰e‚Ì‚Ú‚©‚µ‚Ì‘å‚«‚³
	const double SHADOW_SPREAD      = 10.0; // ‰e‚ÌL‚ª‚è•û
}


void Robot::CentipedeEnemy::update()
{
	// æ“ª‚ÍgetGoalPosŠÖ”‚ÅŽw’è‚³‚ê‚½–Ú“I’n‚ÖˆÚ“®
	if (GameManager::Instance().isWalkingAblePos(getGoalPos()))
	{
		_bodyList[LEADER_INDEX]->setGoalPos(getGoalPos());
	}

	for (int i = 1; i < _bodyList.size(); ++i)
	{
		// Ž©•ª‚æ‚è‘O‚Ì“G‚ð’ÇÕ
		if ((_bodyList[i]->getPos() - _bodyList[i-1]->getPos()).length() < BODY_DISTANCE)
		{
			continue;
		}
		_bodyList[i]->setGoalPos(_bodyList[i - 1]->getPos());
	}

	for (auto && body : _bodyList)
	{
		body->update();
	}
}


void Robot::CentipedeEnemy::draw() const
{
	for (const auto & body : _bodyList)
	{
		body->draw();
	}
}


void Robot::CentipedeEnemy::drawLight() const
{
	Circle(_bodyList[LEADER_INDEX]->getPos(), RADIUS).drawShadow(Vec2::Zero, SHADOW_BLUR_RADIUS, SHADOW_SPREAD, Color(Palette::MyWhite, 0x50));
}
