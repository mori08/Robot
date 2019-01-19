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
		
		size_t _drawTextLength; // 描画するテキストの長さ

		String _text;           // 表示するテキスト

		String _speakerName;    // 話し手の名前

		String _iconName;       // 表示するアイコンの名前

	public:

		TextBox()
			: _drawTextLength(0)
		{
		}

		/// <summary>
		/// 表示するテキストなどの設定
		/// </summary>
		/// <param name="text"> 表示するテキスト </param>
		/// <param name="speakerName"> 話し手の名前 </param>
		/// <param name="iconName"> 表示するアイコンの名前 </param>
		void set(const String & text, const String & speakerName, const String & iconName);

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
			_drawTextLength >= _text.length;
		}

	};
}