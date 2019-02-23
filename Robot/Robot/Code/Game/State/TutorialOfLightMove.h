#pragma once


#include "../GameManager.h"


namespace Robot
{
	/*
	TutorialOfLightMoveクラス
	光の動作のチュートリアル
	*/
	class TutorialOfLightMove : public GameState
	{
	private:

		int _frameCount;     // 経過フレーム数

	public:

		TutorialOfLightMove();

	private:

		void update(GameManager & gameManager) override;

		void draw(const GameManager & gameManager) const override;

	};
}