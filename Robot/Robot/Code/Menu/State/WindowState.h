#pragma once


#include <Siv3D.hpp>


namespace Robot
{
	class MenuWindowBase;

	/*
	WindowState�N���X
	�E�B���h�E�̏�Ԃ�\�����܂�
	*/
	class WindowState
	{
	public:

		/// <summary>
		/// �X�V
		/// </summary>
		/// <param name="window"> �E�B���h�E </param>
		virtual void update(MenuWindowBase & window) = 0;

		/// <summary>
		/// �`��
		/// </summary>
		/// <param name="window"> �E�B���h�E </param>
		virtual void draw(const MenuWindowBase & window) const = 0;

	};
}