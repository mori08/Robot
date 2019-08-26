#pragma once


#include "PlayingState.h"


namespace Robot
{
	/*
	TutorialOfPlayerMove�N���X
	�v���C���[�̓���̃`���[�g���A��
	*/
	class TutorialOfPlayerMove : public PlayingState
	{
	private:

		Vec2   _prePlayerPos;   // 1�t���[���O�̃v���C���[�̍��W
		double _playerMoveDist; // �v���C���[�̈ړ�����
		size_t _frameCount;     // �o�߃t���[����

	public:

		TutorialOfPlayerMove();

	private:

		void update() override;

		void draw() const override;

	};
}