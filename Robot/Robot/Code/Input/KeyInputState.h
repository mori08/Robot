#pragma once


#include"InputState.h"


namespace Robot
{
	/*
	KeyInputState�N���X
	�L�[�{�[�h�ł̓��͂��s���Ƃ���
	InputState�����̏�Ԃɂ��܂��B
	*/
	class KeyInputState : public InputState
	{
	private:

		bool decesion() const override;

		bool option() const override;

		Point direction() const override;

		Optional<String> selectButton(ButtonPtr & selectedButton, const ButtonList &) const override;

	private:

		/// <summary>
		/// �L�[�������ꂽ�Ƃ��{�^���̑I����ύX���܂��B
		/// </summary>
		/// <param name="key"> �L�[ </param>
		/// <param name="selectedButton"> �I�����Ă���{�^�� </param>
		/// <param name="adjacentButton"> �אڂ��Ă���{�^�� </param>
		void checkAndChangeSelectedButton(const Key & key,ButtonPtr & selectedButton, const ButtonPtr & adjacentButton) const;

	};

}