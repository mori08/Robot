#pragma once


#include "PlayingState.h"


namespace Robot
{
	/*
	TutorialOfLightMove�N���X
	���̓���̃`���[�g���A��
	*/
	class TutorialOfLightMove : public PlayingState
	{
	private:

		int _frameCount;     // �o�߃t���[����

	public:

		TutorialOfLightMove();

	private:

		void update() override;

		void draw() const override;

	};
}