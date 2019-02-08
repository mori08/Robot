#pragma once


#include"GameManager.h"


namespace Robot
{
	class TestGameObject : public GameObject
	{
	public:

		TestGameObject();

	private:

		void update(GameManager & gameManager) override;

		void draw() const override;

	};
}