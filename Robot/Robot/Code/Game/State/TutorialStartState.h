#pragma once


#include "PlayingState.h"


namespace Robot
{
	/*
	TutorialStartState
	�`���[�g���A���̂͂���
	*/
	class TutorialStartState : public PlayingState
	{
	private:

		int _framecount; // �o�߃t���[����

	private:

		void update() override;

		void draw() const override;

	};
}