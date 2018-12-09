#pragma once


#include<Siv3D.hpp>


namespace Robot
{
	/*
	Light�N���X
	�^�C�g���V�[���ɗ�����
	*/
	class Light
	{
	private:

		Rect  _region;   // ����\������͈�

		Point _velocity; // ���x

	private:

		Light(const Point & velocity, const Rect & region);

	public:

		static const Light get();

	public:

		/// <summary>
		/// �ʒu���X�V���܂��B
		/// </summary>
		void update();

		/// <summary>
		/// �`�悵�܂��B
		/// </summary>
		void draw() const;

		/// <summary>
		/// �폜�����𖞂����������܂��B
		/// </summary>
		/// <returns> �������Ƃ� true , �����łȂ��Ƃ� false </returns>
		bool isEraseAble() const;

	};
}