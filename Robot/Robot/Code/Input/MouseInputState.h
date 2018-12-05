#pragma once


#include"InputState.h"


namespace Robot
{
	/*
	MouseInputState�N���X
	�}�E�X�ł̓��͂��s���Ƃ���
	InputState�����̏�Ԃɂ��܂��B
	*/
	class MosueInputState : public InputState
	{
	private:

		bool decesion() const override;

		bool option() const override;

		Point direction() const override;

		Optional<String> selectButton(ButtonPtr & selectedButton, const ButtonList & buttonList) const override;

	};
}