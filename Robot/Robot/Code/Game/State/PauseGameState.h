#pragma once


#include "../GameManager.h"


namespace Robot
{
	/*
	PauseGameStateクラス
	ゲームを一時停止し
	続ける・やり直す・メニューに戻る
	を選択させる
	*/
	class PauseGameState : public GameState
	{
	private:

		RectF _cursor;

	public:

		PauseGameState();

	private:

		void update() override;

		void draw() const override;

	private:

		/// <summary>
		/// ボタン名を表示
		/// </summary>
		/// <param name="y"> y座標 </param>
		/// <param name="name"> ボタン名 </param>
		void drawButtonName(int y, const String & name) const;

	};
}