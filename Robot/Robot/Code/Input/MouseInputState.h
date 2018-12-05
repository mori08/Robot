#pragma once


#include"InputState.h"


namespace Robot
{
	/*
	MouseInputStateクラス
	マウスでの入力を行うときに
	InputStateをこの状態にします。
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