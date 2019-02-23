#pragma once


#include "../GameManager.h"


namespace Robot
{
	/*
	TutorialOfLightMove�N���X
	���̓���̃`���[�g���A��
	*/
	class TutorialOfLightMove : public GameState
	{
	private:

		int _frameCount;     // �o�߃t���[����

	public:

		TutorialOfLightMove();

	private:

		void update(GameManager & gameManager) override;

		void draw(const GameManager & gameManager) const override;

	};
}