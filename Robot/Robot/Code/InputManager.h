#pragma once


#include"Button.h"


namespace Robot
{
	// �ǂ�ɂ��Ă̓��͂�
	enum class Which
	{
		UP,       // ��
		DOWN,     // ��
		LEFT,     // ��
		RIGHT,    // �E
		DECISION, // ����
		OPTION    // ���j���[/�|�[�Y
	};

	// �ǂ̂悤�ȓ��͂�
	enum class How
	{
		Clicked, // �������u��
		Pressed, // �����Ă���Ƃ�
		Released // �������u��
	};

	/*
	InputManager�N���X
	���͂��Ǘ����܂��B
	�}�E�X�E�L�[�E�R���g���[���̐؂�ւ���
	����ɉ��������͂̎擾�A
	�{�^���ł̓��͂��Ǘ����܂��B
	*/

	class InputManager
	{
	private:

		using ButtonList = std::unordered_map<String, std::shared_ptr<Button>>;

		using InputList  = std::unordered_map<Which, std::unordered_map<How, bool>>;

	private:

		ButtonList _buttonList; // �Ǘ����Ă���{�^���̃��X�g

		InputList  _inputList;  // �e���͂ɂ��Ẵt���O�Ǘ��p���X�g

		std::function<void(void)> setInput; // �e���͂̃Z�b�g

	private:

		InputManager()
		{
		}

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
		/// �S���͂����Z�b�g���܂��B
		/// </summary>
		void resetInputList();

		/// <summary>
		/// �{�^����o�^���܂��B
		/// </summary>
		/// <param name="key"> �L�[ </param>
		/// <param name="region"> �}�E�X���͗p�͈� </param>
		void registerButton(const String & key, const Rect & region);

	private:

	};

}