#pragma once


namespace Robot
{
	class GameManager;

	/*
	GameStateクラス
	GameManagerにおける状態
	*/
	class GameState
	{
	public:

		/// <summary>
		/// 更新
		/// </summary>
		virtual void update() = 0;

		/// <summary>
		/// 描画
		/// </summary>
		virtual void draw() const = 0;

	};
}