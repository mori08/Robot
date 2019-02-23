#pragma once


#include "../GameManager.h"


namespace Robot
{
	/*
	TutorialOfPlayerMove�N���X
	�v���C���[�̓���̃`���[�g���A��
	*/
	class TutorialOfPlayerMove : public GameState
	{
	private:

		Vec2   _prePlayerPos;   // 1�t���[���O�̃v���C���[�̍��W
		double _playerMoveDist; // �v���C���[�̈ړ�����
		size_t _frameCount;     // �o�߃t���[����

	public:

		TutorialOfPlayerMove();

	private:

		void update(GameManager & gameManager) override;

		void draw(const GameManager & gameManager) const override;

	};
}