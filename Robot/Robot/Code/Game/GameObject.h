#pragma once


#include<Siv3D.hpp>


namespace Robot
{
	class GameManager;

	class GameObject
	{
	protected:
		
		Vec2 _pos; // ���W

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

	};
}