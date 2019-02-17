#pragma once


#include"../GameManager.h"


namespace Robot
{
	class PlayingState : public GameState
	{
	private:

		void update(GameManager & gameManager) override;

		void draw(const GameManager & gameManager) const override;

	};
}