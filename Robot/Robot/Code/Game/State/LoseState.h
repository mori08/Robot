#pragma once


#include "../GameManager.h"


namespace Robot
{
	/*
	LoseEventクラス
	負けイベ用の状態
	*/
	class LoseState : public GameState
	{
	private:

		int   _frameCount;     // 経過フレーム数

		Color _backColor;      // 背景色

		Color _cellColor;      // マスの色

		Size  _textDrawRegion; // 画像を表示する範囲

	public:

		LoseState();

	private:

		void update() override;

		void draw() const override;

		/// <summary>
		/// 色のアルファ値を加算します。
		/// </summary>
		/// <param name="color"> 色 </param>
		/// <param name="addValue"> 加算する値 </param>
		static void addAlpha(Color & color, int addValue);

	};
}