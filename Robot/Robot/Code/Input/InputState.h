#pragma once


#include"Button.h"


namespace Robot
{
	class InputState
	{
	private:

		using ButtonPtr = std::shared_ptr<Button>;

		using ButtonList = std::unordered_map<String, ButtonPtr>;

	public:

		/// <summary>
		/// 決定が入力されたか示します。
		/// </summary>
		/// <returns> 入力されていた時 true , そうでないとき false </returns>
		virtual bool decesion() const = 0;

		/// <summary>
		/// オプションが入力されたか示します。
		/// </summary>
		/// <returns> 入力されていたとき true , そうでないとき false </returns>
		virtual bool option() const = 0;

		/// <summary>
		/// 入力された方向を示します。
		/// </summary>
		/// <returns> 入力された方向 </returns>
		virtual Point direction() const = 0;

		/// <summary>
		/// ボタンを選択します。
		/// </summary>
		/// <param name="selectedButton"> 選択中のボタン </param>
		/// <param name="buttonList"> ボタンのリスト </param>
		virtual void selectButton(ButtonPtr & selectedButton, Button & buttonList) = 0;

	};
}