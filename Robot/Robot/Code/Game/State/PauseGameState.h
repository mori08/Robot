#pragma once


#include "../GameManager.h"


namespace Robot
{
	/*
	PauseGameState�N���X
	�Q�[�����ꎞ��~��
	������E��蒼���E���j���[�ɖ߂�
	��I��������
	*/
	class PauseGameState : public GameState
	{
	private:

		RectF _cursor;

	public:

		PauseGameState();

	private:

		void update() override;

		void draw() const override;

	private:

		/// <summary>
		/// �{�^������\��
		/// </summary>
		/// <param name="y"> y���W </param>
		/// <param name="name"> �{�^���� </param>
		void drawButtonName(int y, const String & name) const;

	};
}