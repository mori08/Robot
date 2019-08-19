#pragma once


#include "../GameManager.h"


namespace Robot
{
	/*
	LoseEvent�N���X
	�����C�x�p�̏��
	*/
	class LoseState : public GameState
	{
	private:

		int   _frameCount;     // �o�߃t���[����

		Color _backColor;      // �w�i�F

		Color _cellColor;      // �}�X�̐F

		Size  _textDrawRegion; // �摜��\������͈�

	public:

		LoseState();

	private:

		void update() override;

		void draw() const override;

		/// <summary>
		/// �F�̃A���t�@�l�����Z���܂��B
		/// </summary>
		/// <param name="color"> �F </param>
		/// <param name="addValue"> ���Z����l </param>
		static void addAlpha(Color & color, int addValue);

	};
}