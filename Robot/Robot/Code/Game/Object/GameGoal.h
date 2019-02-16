#pragma once


#include"../GameManager.h"


namespace Robot
{
	/*
	GameGaolクラス
	Playerがこのオブジェクトに触れた時
	クリアとなります。
	*/
	class GameGoal : public GameObject
	{
	public:

		/// <summary>

		GameGoal(const Vec2 & pos)
			: GameObject(pos)
		{

		}

	private:

		void update(GameManager & gameManager) override;

		void draw() const override;

	};
}