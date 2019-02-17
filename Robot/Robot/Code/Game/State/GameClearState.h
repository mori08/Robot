#pragma once


#include "../GameManager.h"


namespace Robot
{
	/*
	GameClearState�N���X
	�Q�[���ɃN���A�����Ƃ��̏��
	*/
	class GameClearState : public GameState
	{
	private:

		int   _frameCount; // �o�߃t���[����

		Color _backColor;  // �w�i�F

		Color _lightColor; // ���S�ɕ`�悷����̐F

		double _smallLightDist;

		Array<Vec2> _smallLightDirectionList; // �����Ȍ���`�悷�钆�S����̕����̃��X�g

	public:

		GameClearState();

	private:

		void update(GameManager & gameManager) override;

		void draw(const GameManager & gameManager) const override;

		/// <summary>
		/// �F�̃A���t�@�l�����Z���܂��B
		/// </summary>
		/// <param name="color"> �F </param>
		/// <param name="addValue"> ���Z����l </param>
		static void addAlpha(Color & color,int addValue);

	};
}