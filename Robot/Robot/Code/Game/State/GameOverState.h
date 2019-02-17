#pragma once


#include "../GameManager.h"


namespace Robot
{
	/*
	GameOverState�N���X
	�Q�[���I�[�o�[�����Ƃ��̏��
	*/
	class GameOverState : public GameState
	{
	private:

		int   _frameCount;     // �o�߃t���[����

		Color _backColor;      // �w�i�F

		Color _cellColor;      // �}�X�̐F

		Size  _textDrawRegion; // �摜��\������͈�

		RectF _cursor;         // �J�[�\��

	public:

		GameOverState();

	private:

		void update(GameManager & gameManager) override;

		void draw(const GameManager & gameManager) const override;

		/// <summary>
		/// �F�̃A���t�@�l�����Z���܂��B
		/// </summary>
		/// <param name="color"> �F </param>
		/// <param name="addValue"> ���Z����l </param>
		static void addAlpha(Color & color, int addValue);

	};
}