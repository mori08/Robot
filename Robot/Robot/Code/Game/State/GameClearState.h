#pragma once


#include "../GameManager.h"


namespace Robot
{
	/*
	GameClearStateクラス
	ゲームにクリアしたときの状態
	*/
	class GameClearState : public GameState
	{
	private:

		int   _frameCount; // 経過フレーム数

		Color _backColor;  // 背景色

		Color _lightColor; // 中心に描画する光の色

		double _smallLightDist;

		Array<Vec2> _smallLightDirectionList; // 小さな光を描画する中心からの方向のリスト

	public:

		GameClearState();

	private:

		void update() override;

		void draw() const override;

		/// <summary>
		/// 色のアルファ値を加算します。
		/// </summary>
		/// <param name="color"> 色 </param>
		/// <param name="addValue"> 加算する値 </param>
		static void addAlpha(Color & color,int addValue);

	};
}