#pragma once


#include<Siv3D.hpp>
#include"State/WindowState.h"
#include"../../Input/Button.h"


namespace Robot
{
	class MenuScene;

	/*
	MenuWindowBaseクラス
	MenuSceneに表示するWindowwoを表す
	*/
	class MenuWindowBase
	{
	protected:

		using Processing    = std::function<void()>;
		using ProcessingPtr = std::unique_ptr<std::function<void()>>;

	public:

		static const ColorF NON_SHOWED_COLOR;
		static const ColorF SHOWED_COLOR;
		static const ColorF NON_SELECTED_COLOR;
		static const ColorF SELECTED_COLOR;

	protected:

		std::unique_ptr<WindowState>              _state;         // 状態

		std::vector<std::shared_ptr<Button>>      _buttonPtrList; // ボタンのポインタのリスト
		
		std::unordered_map<String, ProcessingPtr> _processingMap; // ボタンを押したときの処理リスト

		ColorF        _white;             // 白色

		RectF         _cursor;            // カーソル

		ProcessingPtr _closedProcessing;  // ウィンドウを閉じるときの処理

		String        _selectedButtonKey; // 選択されているボタンのキー

		Vec2          _openOffset;        // ウィンドウを開くときの演出開始位置

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
		/// ウィンドウを選択します。
		/// </summary>
		void select();

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
		/// ウィンドウを閉じたときの処理を設定します。
		/// </summary>
		void setClosedProcessing(ProcessingPtr processing)
		{
			_closedProcessing = std::move(processing);
		}

	public: // WindowStateで使用

		/// <summary>
		/// ボタンの色を変更します。
		/// </summary>
		/// <param name="color"> 色 </param>
		void setColor(const ColorF & color);

		/// <summary>
		/// ボタンの数を取得します
		/// </summary>
		int numOfButton() const
		{
			return (int)_buttonPtrList.size();
		}

		/// <summary>
		/// 選択中の更新
		/// </summary>
		void updateSelectedWindowButton();

		/// <summary>
		/// ボタンと光を描画します。
		/// </summary>
		/// <param name="offsetList"> ずらし </param>
		void drawButtonAndLight(const Vec2 & offset = Vec2::Zero) const;

		/// <summary>
		/// 状態を変更します。
		/// </summary>
		void changeState(std::unique_ptr<WindowState> state)
		{
			_state = std::move(state);
		}

	protected:

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
		/// <param name="processing"> ボタンを押したときの処理 </param>
		void registerButton(const String & buttonKey, const Rect & region, ProcessingPtr processing);

	private:

		/// <summary>
		/// 色を変更します
		/// </summary>
		/// <param name="color"> 変更したい色 </param>
		/// <param name="goalColor"> 変更先 </param>
		static void changeColor(ColorF & color, const ColorF & goalColor);

	};
}
