#pragma once


#include<Siv3D.hpp>


namespace Robot
{
	class Button
	{
	private:

		static const int ADJACENT_BUTTON_SIZE = 4;                                 // �אڂ���{�^���̐�

		std::array<std::shared_ptr<Button>, ADJACENT_BUTTON_SIZE> _adjacentButtonList; // �אڂ���{�^���̃|�C���^

		const String _key;    // �o�͗p�̃L�[

		const Rect   _region; // �}�E�X���͎��̗L���͈�

	public:

		static const int UP    = 0; // ��
		static const int DOWN  = 1; // ��
		static const int RIGHT = 2; // �E
		static const int LEFT  = 3; // ��

	public:

		/// <summary>
		/// �{�^��
		/// <param name="key"> �o�͗p�̃L�[ </param>
		/// <param name="region"> �}�E�X���͎��̗L���͈� </param>
		Button(const String & key,const Rect region);

		/// <summary>
		/// �אڂ���{�^����ݒ肵�܂��B
		/// </summary>
		/// <param name="direction"> ���� </param>
		/// <param name="adjacentButton"> �אڂ���{�^�� </param> 
		void setAdjacentButton(int direction, std::shared_ptr<Button> adjacentButton);

		/// <summary>
		/// �J�[�\������ɂ��邩�������܂��B
		/// </summary>
		/// <returns> �J�[�\������ɂ���Ƃ� true , �����łȂ��Ƃ� false </returns>
		bool mouseOver() const
		{
			return _region.mouseOver;
		}
	};
}