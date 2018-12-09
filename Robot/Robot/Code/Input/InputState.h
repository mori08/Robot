#pragma once


#include"Button.h"


namespace Robot
{
	/*
		入力の状態の基底
	*/
	class InputState
	{
	protected:

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
		virtual const Point & direction() const = 0;

		/// <summary>
		/// ボタンを選択します。
		/// </summary>
		/// <param name="selectedButton"> 選択中のボタン </param>
		/// <param name="buttonList"> ボタンのリスト </param>
		/// <returns> 
		/// 決定が入力されたときにそのボタンのキーを返します。
		/// 何も選択されていないとき無効値を返します。
		/// </returns>
		/// <remarks>
		/// 入力に応じたボタン選択の変更を行います。
		/// 1フレームに2度以上使用しないでください。
		/// ボタンが登録されていない状態で使用しないでください。
		/// </remarks>
		virtual Optional<String> selectButton(ButtonPtr & selectedButton, const ButtonList & buttonList) const = 0;

		/// <summary>
		/// 状態を切り替える。
		/// </summary>
		/// <param name="inputState"> 入力の状態 </param>
		virtual Optional<String> changeState() const = 0;


	};
}