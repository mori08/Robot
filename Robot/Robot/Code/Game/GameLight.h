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

		bool _off; // true�̂Ƃ����C�g������

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
		/// ���W���擾���܂��B
		/// </summary>
		/// <returns> ���W </returns>
		const Vec2 & getPos() const
		{
			return _pos;
		}

		/// <summary>
		/// ���C�g������
		/// </summary>
		void Off()
		{
			_off = true;
		}

		/// <summary>
		/// ���C�g������
		/// </summary>
		void On()
		{
			_off = false;
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