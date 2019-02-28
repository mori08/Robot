#pragma once


#include<Siv3D.hpp>
#include"State/WindowState.h"
#include"../../Input/Button.h"


namespace Robot
{
	/*
	MenuWindowBaseクラス
	MenuSceneに表示するWindowwoを表す
	*/
	class MenuWindowBase
	{
	private:

		using ProcessingPtr = std::unique_ptr<std::function<void()>>;

	public:

		static const ColorF NON_SHOWED_COLOR;
		static const ColorF NON_SELECTED_COLOR;
		static const ColorF SELECTED_COLOR;

	protected:

		std::unique_ptr<WindowState>              _state;         // 状態

		std::vector<std::shared_ptr<Button>>      _buttonPtrList; // ボタンのポインタのリスト
		
		std::unordered_map<String, ColorF>        _colorMap;      // 色のリスト ボタンのキーと結びつける

		std::unordered_map<String, ProcessingPtr> _processingMap; // ボタンを押したときの処理リスト

		String _selectedButtonKey; // 選択されているボタンのキー

	public: // MenuSceneで使用

		MenuWindowBase();

		/// <summary>
		/// 更新
		/// </summary>
		virtual void update();

		/// <summary>
		/// 描画
		/// </summary>
		virtual void draw() const;

		/// <summary>
		/// ウィンドウを開きます。
		/// </summary>
		void open();

		/// <summary>
		/// ウィンドウの選択を外します。
		/// </summary>
		void nonSelect();

		/// <summary>
		/// ウィンドウを閉じます。
		/// </summary>
		void close();

		/// <summary>
		/// InputManagerにボタンの情報を更新します。
		/// </summary>
		virtual void updateInputManager() const = 0;

		/// <summary>
		/// ボタンを押したときの処理を設定します。
		/// </summary>
		/// <param name="buttonKey"> ボタンのキー </param>
		/// <param name="processing"> ボタンを押したときの処理 </param>
		void setClickedProcessing(const String & buttonKey, ProcessingPtr processing);
		
	public: // WindowStateで使用

		/// <summary>
		/// ボタンの色を変更します。
		/// </summary>
		/// <param name="color"> 色 </param>
		/// <param name="num"> 変更する個数 </param>
		void setColor(const Color color, size_t num = String::npos);

		/// <summary>
		/// 選択中の更新
		/// </summary>
		void updateSelectedWindowButton();

		/// <summary>
		/// ボタンと光を描画します。
		/// </summary>
		void drawButtonAndLight() const;

	protected:

		/// <summary>
		/// 指定されたキーを持つボタンがあるか示します。
		/// </summary>
		/// <param name="buttonKey"> ボタンのキー </param>
		/// <returns> キーがあるとき true , そうでないとき false </returns>
		/// <remarks>
		/// O(ボタンの数)だけの時間がかかります
		/// </remarks>
		bool keyExistsAtButtonList(const String & buttonKey) const;

		/// <summary>
		/// 指定された処理があるか示します。
		/// </summary>
		/// <param name="buttonKey"> ボタンのキー </param>
		bool processingExists(const String & buttonKey) const
		{
			return _processingMap.find(buttonKey) != _processingMap.end();
		}

		/// <summary>
		/// ボタン登録に関わる一連の処理を行います。
		/// </summary>
		/// <param name="butttonKey"> ボタンのキー </param>
		/// <param name="region"> 範囲 </param>
		void registerButton(const String & buttonKey, const Rect & region);

	private:

		/// <summary>
		/// 色を変更します
		/// </summary>
		/// <param name="color"> 変更したい色 </param>
		/// <param name="goalColor"> 変更先 </param>
		static void changeColor(ColorF & color, const ColorF & goalColor);

	};
}
