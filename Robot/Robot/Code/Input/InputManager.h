#pragma once


#include"Button.h"
#include"InputState.h"


namespace Robot
{
	/*
	InputManager�N���X
	���͂��Ǘ����܂��B
	�}�E�X�E�L�[�{�[�h�̐؂�ւ���
	����ɉ��������͂̎擾�A
	�{�^���ł̓��͂��Ǘ����܂��B
	*/

	class InputManager
	{
	private:

		using ButtonPtr  = std::shared_ptr<Button>;

		using ButtonList = std::unordered_map<String, ButtonPtr>;

	private:

		ButtonList                  _buttonList;     // �Ǘ����Ă���{�^���̃��X�g

		ButtonPtr                   _selectedButton; // �I�����Ă���{�^��

		std::unique_ptr<InputState> _inputState;     // ���͕��@�ɂ��Ă̏��

	private:

		InputManager();

		InputManager(const InputManager&)            = default;
		InputManager& operator=(const InputManager&) = default;
		InputManager(InputManager&&)                 = default;
		InputManager& operator=(InputManager&&)      = default;

	public:

		/// <summary>
		/// �V���O���g���Ƃ��ĊǗ����Ă���InputManager�̃C���X�^���X���擾���܂��B
		/// </summary>
		/// <returns> �C���X�^���X </returns>
		static InputManager & Instance()
		{
			static InputManager inputManager;
			return inputManager;
		}

		/// <summary>
		/// �{�^����o�^���܂��B
		/// </summary>
		/// <param name="key"> �L�[ </param>
		/// <param name="region"> �}�E�X���͗p�͈� </param>
		void registerButton(const String & key, const Rect & region);

		/// <summary>
		/// �{�^����o�^���܂��B
		/// </summary>
		/// <param name="button"> �{�^�� </param>
		void registerButton(ButtonPtr button)
		{
			_buttonList[button->getKey()] = button;
		}

		/// <summary>
		/// �{�^���̐��������̗אڊ֌W��ݒ肵�܂��B
		/// </summary>
		/// <param name="upKey"> �����̃{�^���̃L�[ </param>
		/// <param name="downKey"> �E���̃{�^���̃L�[ </param>
		void setVerticalAdjacentButton(const String & upKey, const String & downKey);

		/// <summary>
		/// �{�^���̐��������̗אڊ֌W��ݒ肵�܂��B
		/// </summary>
		/// <param name="leftKey"> �����̃{�^���̃L�[ </param>
		/// <param name="rightKey"> �E���̃{�^���̃L�[ </param>
		void setHorizontalAdjacentButton(const String & leftKey, const String & rightKey);

		/// <summary>
		/// �I�𒆂̃{�^����ݒ肵�܂��B
		/// </summary>
		/// <param name="key"> �{�^���̃L�[ </param>
		void setSelectedButton(const String & key);

		/// <summary>
		/// �I�𒆂̃{�^�����擾���܂��B
		/// </summary>
		/// <returns> �I�𒆂̃{�^�� </returns>
		const Button & getSelectedButton() const
		{
			return *_selectedButton;
		}

		/// <summary>
		/// �{�^���̃��X�g����ɂ��܂��B
		/// </summary>
		void clearButtonList()
		{
			_selectedButton = nullptr;
			_buttonList.clear();
		}

		/// <summary>
		/// ���肪���͂��ꂽ�������܂��B
		/// </summary>
		/// <returns> ���͂���Ă����� true , �����łȂ��Ƃ� false </returns>
		bool decision() const
		{
			return _inputState->decesion();
		}

		/// <summary>
		/// �I�v�V���������͂��ꂽ�������܂��B
		/// </summary>
		/// <returns> ���͂���Ă����Ƃ� true , �����łȂ��Ƃ� false </returns>
		bool option() const
		{
			return _inputState->option();
		}

		/// <summary>
		/// ���͂��ꂽ�����������܂��B
		/// </summary>
		/// <returns> ���͂��ꂽ���� </returns>
		Point directon() const
		{
			return std::move(_inputState->direction());
		}

		/// <summary>
		/// �{�^����I�����܂��B
		/// </summary>
		/// <param name="selectedButton"> �I�𒆂̃{�^�� </param>
		/// <param name="buttonList"> �{�^���̃��X�g </param>
		/// <returns> 
		/// ���肪���͂��ꂽ�Ƃ��ɂ��̃{�^���̃L�[��Ԃ��܂��B
		/// �����I������Ă��Ȃ��Ƃ������l��Ԃ��܂��B
		/// </returns>
		/// <remarks>
		/// ���͂ɉ������{�^���I���̕ύX���s���܂��B
		/// 1�t���[����2�x�ȏ�g��Ȃ��ł��������B
		/// </remarks>
		Optional<String> selectButton()
		{
			return _inputState->selectButton(_selectedButton, _buttonList);
		}

		/// <summary>
		/// ���͕��@�ɂ��Ă̏�Ԃ�ύX���܂��B
		/// </summary>
		void changeState();

	};

}