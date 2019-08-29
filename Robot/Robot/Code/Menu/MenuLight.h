#pragma once


#include <Siv3D.hpp>


namespace Robot
{
	/*
	MenuLight�N���X
	���j���[�V�[���ɗ�����
	*/
	class MenuLight
	{
	private:

		Circle _region; // ����\������͈�

		double _speed;  // ����

		int    _alpha;  // �F

	private:

		/// <param name="x"> ��������x���W </param>
		/// <param name="r"> ���a(�����͂���̓��ɔ��) </param>
		MenuLight(double x, double r);

	public:

		bool operator<(const MenuLight & light) const;

	public:

		static const MenuLight get();

	public:

		/// <summary>
		/// �X�V
		/// </summary>
		void update();

		/// <summary>
		/// �`��
		/// </summary>
		void draw() const;

		/// <summary>
		/// �폜�����𖞂����������܂��B
		/// </summary>
		/// <returns> �������Ƃ� true , �����łȂ��Ƃ� false </returns>
		bool isEraseAble() const;

	};
}