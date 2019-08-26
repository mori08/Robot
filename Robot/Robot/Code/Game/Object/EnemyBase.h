#pragma once


#include "../GameManager.h"


namespace Robot
{
	/*
	EnemyBase�N���X
	GameObject�N���X�̔h���N���X
	�쐬����G�̊��N���X�ƂȂ�
	�v���C���[�ƂԂ������Ƃ��̏���
	�G�̉摜�̕`��
	*/
	class EnemyBase : public GameObject
	{
	protected:

		int   _frameCount; // �o�߃t���[����

		Point _texturePos; // �`�悷��摜�̔ԍ�

	public:

		EnemyBase(const Vec2 & pos);

		virtual void update() override;

		virtual void draw() const override;

	protected:

		/// <summary>
		/// �ړ��x�N�g�������߂܂��B
		/// </summary>
		/// <returns> �ړ��x�N�g�� </returns>
		virtual Vec2 getMoveVec() = 0;

		/// <summary>
		/// �v���C���[�ƐڐG�����Ƃ��̏���
		/// </summary>
		virtual void gameOver();

	};
}