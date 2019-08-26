#include "GameGoal.h"
#include "../State/GameClearState.h"


namespace
{
	const double CLEAR_DISTANCE = 5.0; // �N���A���肪�s���鋗��

	const Size   TEXTURE_SIZE(40, 40); // �摜�̃T�C�Y

	const int    CHANGE_TEXTURE_SPAN=10;  // �摜��ύX����t���[����
}


void Robot::GameGoal::update()
{
	if (++_frameCount%CHANGE_TEXTURE_SPAN == 0)
	{
		_texturePos.x++;
	}

	moveObject(getMoveVec());

	GameManager::Instance().setGoalPos(_pos);

	if ((_pos - GameManager::Instance().getPlayerPos()).length() < CLEAR_DISTANCE)
	{
		GameManager::Instance().changeGameState(std::make_unique<GameClearState>());
	}

}

void Robot::GameGoal::draw() const
{
	TextureAsset(L"Goal")(_texturePos*TEXTURE_SIZE,TEXTURE_SIZE).drawAt(_pos);
}
