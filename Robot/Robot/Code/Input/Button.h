#pragma once


#include<Siv3D.hpp>


namespace Robot
{

	/*
	Button�N���X
	�אڂ���{�^�����ɃJ�[�\�������邩�Ȃǂ������܂��B
	InputManager�N���X�Ŏg�p���܂��B
	*/

	class Button
	{
	private:

		static const int ADJACENT_BUTTON_SIZE = 4;                                     // �אڂ���{�^���̐�

		std::array<std::shared_ptr<Button>, ADJACENT_BUTTON_SIZE> _adjacentButtonList; // �אڂ���{�^���̃|�C���^

		const String _key;    // �o�͗p�̃L�[

		const Rect   _region; // �}�E�X���͎��̗L���͈�

	public:

		static const int UP    = 0; // ��
		static const int DOWN  = 1; // ��
		static const int LEFT  = 2; // ��
		static const int RIGHT = 3; // �E

	public:

		/// <summary>
		/// �{�^��
		/// </summary>
		/// <param name="key"> �o�͗p�̃L�[ </param>
		/// <param name="region"> �}�E�X���͎��̗L���͈� </param>
		Button(const String & key,const Rect & region);

		/// <summary>
		/// �אڂ���{�^����ݒ肵�܂��B
		/// </summary>
		/// <param name="direction"> ���� </param>
		/// <param name="adjacentButton"> �אڂ���{�^�� </param> 
		void setAdjacentButton(int direction, std::shared_ptr<Button> adjacentButton)
		{
#ifdef _DEBUG
			if (direction < 0 || direction > ADJACENT_BUTTON_SIZE)
			{
				Println(L"Error > setAdjuacnetButton�ŕs�K�؂ȓ��� : ", direction);
				return;
			}
#endif // _DEBUG

			_adjacentButtonList[direction] = adjacentButton;
		}

		/// <summary>
		/// �אڂ���{�^�����擾���܂��B
		/// </summary>
		/// <param name="direction"> ���� </param>
		/// <returns> �אڂ���{�^���̃|�C���^ </returns>
		std::shared_ptr<Button> getAdjacentButton(int direction) const
		{
#ifdef _DEBUG
			if (direction < 0 || direction > ADJACENT_BUTTON_SIZE)
			{
				Println(L"Error > setAdjuacnetButton�ŕs�K�؂ȓ��� : ", direction);
				return nullptr;
			}
#endif // _DEBUG

			return _adjacentButtonList[direction];
		}

		/// <summary>
		/// �L�[���擾���܂��B
		/// </summary>
		String getKey() const
		{
			return _key;
		}

		/// <summary>
		/// �}�E�X���͎��̗L���͈͂��擾���܂��B
		/// </summary>
		/// <returns> �}�E�X���͎��̗L���͈� </returns>
		const Rect & getRegion() const
		{
			return _region;
		}

	};
}