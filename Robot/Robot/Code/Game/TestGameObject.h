#pragma once


#include"GameManager.h"


namespace Robot
{
	/*
	TestGameObjectクラス
	経路探索や描画が正しく行われているかテストします。
	*/
	class TestGameObject : public GameObject
	{
	public:

		TestGameObject();

	private:

		void update(GameManager & gameManager) override;

		void draw() const override;

	};
}