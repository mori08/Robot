#pragma once


#include "../GameManager.h"


namespace Robot
{
	/*
	TutorialOfSearchGoal�N���X
	�S�[���̒T���̃`���[�g���A��
	*/
	class TutorialOfSearchGoal : public GameState
	{
	private:

		size_t _frameCount; // �o�߃t���[����

	public:

		TutorialOfSearchGoal();

	private:

		void update() override;

		void draw() const override;

	};
}