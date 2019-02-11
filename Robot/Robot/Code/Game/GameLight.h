#pragma once


#include<Siv3D.hpp>


namespace Robot
{
	/*
	GameLight�N���X
	Game�V�[���Ń}�b�v���Ƃ炵�܂�
	*/
	class GameLight
	{
	private:

		Vec2 _pos; // ���̒��S���W

	public:

		/// <summary>
		/// ���W��ݒ肵�܂�
		/// </summary>
		/// <param name="pos"> ���W </param>
		void setPos(const Vec2 & pos)
		{
			_pos = pos;
		}

		/// <summary>
		/// �`��
		/// </summary>
		void update();

		/// <summary>
		/// �`��
		/// </summary>
		void draw() const;

	};
}