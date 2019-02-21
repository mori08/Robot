#include "GameGoal.h"


namespace
{
	const double CLEAR_DISTANCE = 5.0; // クリア判定が行われる距離

	const Size   TEXTURE_SIZE(40, 40); // 画像のサイズ

	const int    CHANGE_TEXTURE_SPAN=10;  // 画像を変更するフレーム数
}


void Robot::GameGoal::update(GameManager & gameManager)
{
	if (++_frameCount%CHANGE_TEXTURE_SPAN == 0)
	{
		_texturePos.x++;
	}

	if ((_pos - gameManager.getPlayerPos()).length() < CLEAR_DISTANCE)
	{
		gameManager.gameClear();
	}
}

void Robot::GameGoal::draw() const
{
	TextureAsset(L"Goal")(_texturePos*TEXTURE_SIZE,TEXTURE_SIZE).drawAt(_pos);
}
