#pragma once


#include "../GameManager.h"


namespace Robot
{
	/*
	TutorialStartState
	�`���[�g���A���̂͂���
	*/
	class TutorialStartState : public GameState
	{
	private:

		int _framecount; // �o�߃t���[����

	private:

		void update(GameManager & gameManager) override;

		void draw(const GameManager & gameManager) const override;

	};
}