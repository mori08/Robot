#pragma once


#include<Siv3D.hpp>
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

	protected:

		std::vector<std::shared_ptr<Button>>      _buttonPtrList; // ボタンのポインタのリスト
		
		std::unordered_map<String, ColorF>        _colorMap;      // 色のリスト ボタンのキーと結びつける

		std::unordered_map<String, ProcessingPtr> _processingMap; // ボタンを押したときの処理リスト

		String _selectedButtonKey; // 選択されているボタンのキー

	public:

		/// <summary>
		/// 更新
		/// </summary>
		virtual void update();

		/// <summary>
		/// 描画
		/// </summary>
		virtual void draw() const = 0 ;

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
		
	protected:

		/// <summary>
		/// ボタンを照らす光を描画します。
		/// </summary>
		void drawLight() const;

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
