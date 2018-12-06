#pragma once


#include"Button.h"
#include"InputState.h"


namespace Robot
{
	/*
	InputManagerクラス
	入力を管理します。
	マウス・キーボードの切り替えや
	それに応じた入力の取得、
	ボタンでの入力を管理します。
	*/

	class InputManager
	{
	private:

		using ButtonPtr  = std::shared_ptr<Button>;

		using ButtonList = std::unordered_map<String, ButtonPtr>;

	private:

		ButtonList                  _buttonList;     // 管理しているボタンのリスト

		ButtonPtr                   _selectedButton; // 選択しているボタン

		std::unique_ptr<InputState> _inputState;     // 入力方法についての状態

	private:

		InputManager();

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
		/// ボタンを登録します。
		/// </summary>
		/// <param name="key"> キー </param>
		/// <param name="region"> マウス入力用範囲 </param>
		void registerButton(const String & key, const Rect & region);

		/// <summary>
		/// ボタンのリストを空にします。
		/// </summary>
		void clearButtonList()
		{
			_selectedButton = nullptr;
			_buttonList.clear();
		}

		/// <summary>
		/// 決定が入力されたか示します。
		/// </summary>
		/// <returns> 入力されていた時 true , そうでないとき false </returns>
		bool decision() const
		{
			return _inputState->decesion();
		}

		/// <summary>
		/// オプションが入力されたか示します。
		/// </summary>
		/// <returns> 入力されていたとき true , そうでないとき false </returns>
		bool option() const
		{
			return _inputState->option();
		}

		/// <summary>
		/// 入力された方向を示します。
		/// </summary>
		/// <returns> 入力された方向 </returns>
		Point directon() const
		{
			return std::move(_inputState->direction());
		}

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
		/// 1フレームに2度以上使わないでください。
		/// </remarks>
		Optional<String> selectButton()
		{
			return _inputState->selectButton(_selectedButton, _buttonList);
		}

		/// <summary>
		/// 入力方法についての状態を変更します。
		/// </summary>
		void changeState();

	};

}