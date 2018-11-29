#pragma once


#include"Button.h"


namespace Robot
{
	// どれについての入力か
	enum class Which
	{
		UP,       // 上
		DOWN,     // 下
		LEFT,     // 左
		RIGHT,    // 右
		DECISION, // 決定
		OPTION    // メニュー/ポーズ
	};

	// どのような入力か
	enum class How
	{
		Clicked, // 押した瞬間
		Pressed, // 押しているとき
		Released // 離した瞬間
	};

	/*
	InputManagerクラス
	入力を管理します。
	マウス・キー・コントローラの切り替えや
	それに応じた入力の取得、
	ボタンでの入力を管理します。
	*/

	class InputManager
	{
	private:

		using ButtonList = std::unordered_map<String, std::shared_ptr<Button>>;

		using InputList  = std::unordered_map<Which, std::unordered_map<How, bool>>;

	private:

		ButtonList _buttonList; // 管理しているボタンのリスト

		InputList  _inputList;  // 各入力についてのフラグ管理用リスト

		std::function<void(void)> setInput; // 各入力のセット

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
		/// シングルトンとして管理しているInputManagerのインスタンスを取得します。
		/// </summary>
		/// <returns> インスタンス </returns>
		static InputManager & Instance()
		{
			static InputManager inputManager;
			return inputManager;
		}

		/// <summary>
		/// 全入力をリセットします。
		/// </summary>
		void resetInputList();

		/// <summary>
		/// ボタンを登録します。
		/// </summary>
		/// <param name="key"> キー </param>
		/// <param name="region"> マウス入力用範囲 </param>
		void registerButton(const String & key, const Rect & region);

	private:

	};

}