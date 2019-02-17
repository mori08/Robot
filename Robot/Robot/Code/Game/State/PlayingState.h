#pragma once


#include "../GameManager.h"


namespace Robot
{
	/*
	PlayingState�N���X
	�Q�[���v���C����GameManager�̏��
	*/
	class PlayingState : public GameState
	{
	private:

		void update(GameManager & gameManager) override;

		void draw(const GameManager & gameManager) const override;

	};
}