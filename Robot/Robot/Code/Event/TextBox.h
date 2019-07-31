#pragma once


#include<Siv3D.hpp>


namespace Robot
{
	/*
	TextBoxクラス
	イベントでテキストボックスの更新・描画を行います。
	*/
	class TextBox
	{
	private:
		
		bool   _isReady;        // テキストが設定できるか

		int    _drawTextSpan;   // テキストを表示するフレーム数の間隔

		size_t _drawTextLength; // 描画するテキストの長さ

		String _speakerName;    // 話し手の名前

		String _iconName;       // 表示するアイコンの名前

		String _text;           // 表示するテキスト

	public:

		TextBox()
			: _drawTextLength(0)
		{
		}

		/// <summary>
		/// 表示するテキストなどの設定
		/// </summary>
		/// <param name="speakerName"> 話し手の名前 </param>
		/// <param name="iconName"> 表示するアイコンの名前 </param>
		/// <param name="text"> 表示するテキスト </param>
		/// <param name="drawTextSpan"> テキストを表示するフレーム数の間隔 </param>
		void set(const String & speakerName, const String & iconName, const String & text, int dratTextSpan);

		/// <summary>
		/// 初期化
		/// </summary>
		void reset();

		/// <summary>
		/// 更新
		/// </summary>
		void update();

		/// <summary>
		/// 描画
		/// </summary>
		void draw()const;

		/// <summary>
		/// テキストなどを設定できるか示します
		/// </summary>
		/// <returns> 設定できるとき true , そうでないとき false </returns>
		bool isReady() const
		{
			return _isReady;
		}

	};
}