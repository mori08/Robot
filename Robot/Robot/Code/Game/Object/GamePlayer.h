#pragma once


#include"../GameManager.h"


namespace Robot
{
	/*
	GamePlayer�N���X
	GameObject�̔h���N���X�ŁC
	GameManager��Player�Ƃ��Ĉ����D
	�L�[���͂ɉ������ړ�������D
	*/
	class GamePlayer : public GameObject 
	{
	private:

		Point _texturePos; // �`�悷��摜�̔ԍ�

		int   _frameCount; // �o�߃t���[����

	public:

		/// <summary>
		/// GameManager�ł�Player�I�u�W�F�N�g
		/// </summary>
		/// <param name="pos"> �������W </param>
		GamePlayer(const Vec2 & pos);

	private:

		void update(GameManager & gameManager) override;

		void draw() const override;

		/// <summary>
		/// �v���C���[�̈ړ��������L�[���͂��猈�肵�܂��B
		/// </summary>
		/// <returns> �ړ����� </returns>
		Vec2 getMoveVec() const;

	};
}