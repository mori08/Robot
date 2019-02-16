#include "GameGoal.h"


namespace
{
	const double CLEAR_DISTANCE = 5.0; // �N���A���肪�s���鋗��
}


void Robot::GameGoal::update(GameManager & gameManager)
{
	if ((_pos - gameManager.getPlayerPos()).length() < CLEAR_DISTANCE)
	{
		gameManager.Instance().gameClear();
	}
}

void Robot::GameGoal::draw() const
{
	Circle(_pos, 20).drawShadow(Vec2::Zero, 10, 10, Palette::MyBlack);
}
