#pragma once


#include"InputState.h"


namespace Robot
{
	/*
	KeyInputStateクラス
	キーボードでの入力を行うときに
	InputStateをこの状態にします。
	*/
	class KeyInputState : public InputState
	{
	private:

		bool decesion() const override;

		bool option() const override;

		const Point & direction() const override;

		Optional<String> selectButton(ButtonPtr & selectedButton, const ButtonList &) const override;

		Optional<String> changeState() const override;

	private:

		/// <summary>
		/// キーが押されたときボタンの選択先を変更します。
		/// </summary>
		/// <param name="key"> キー </param>
		/// <param name="selectedButton"> 選択しているボタン </param>
		/// <param name="adjacentButton"> 隣接しているボタン </param>
		void checkAndChangeSelectedButton(const Key & key,ButtonPtr & selectedButton, const ButtonPtr & adjacentButton) const;

	};

}