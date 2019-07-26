#pragma once


#include<Siv3D.hpp>


namespace Robot
{
	class GameManager;

	/*
	GameObject�N���X
	GameManager�ň���Object(�v���C���[�E�G�E�S�[���Ȃ�)�̊��N���X
	���̃N���X�̔h���N���X���쐬����Ƃ���
	GameManager��Object�����֐��ɓo�^����
	*/
	class GameObject
	{
	protected:
		
		Vec2 _pos;     // ���W

	public:

		/// <summary>
		/// �Q�[���V�[���ň����I�u�W�F�N�g
		/// </summary>
		GameObject(const Vec2 & pos)
			: _pos(pos)
		{
		}

		/// <summary>
		/// �X�V
		/// </summary>
		/// <param name="gameManager"> GameManager�̃C���X�^���X </param>
		virtual void update(GameManager & gameManager) = 0;

		/// <summary>
		/// �`��
		/// </summary>
		virtual void draw() const = 0;

		/// <summary>
		/// ���̕`��
		/// </summary>
		virtual void drawLight() const
		{
		}

	protected:

		/// <summary>
		/// �I�u�W�F�N�g�̈ʒu���ړ������܂��B
		/// </summary>
		/// <param name="gameManager"> GameManager </param>
		/// <param name="vec"> ���Z������W </param>
		void moveObject(const GameManager & gameManager, const Vec2 & vec);

	};
}