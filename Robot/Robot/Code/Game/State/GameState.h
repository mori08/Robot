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
		/// <param name="gameManager"> GameManagerのインスタンス </param>
		virtual void update(GameManager & gameManager) = 0;

		/// <summary>
		/// 描画
		/// </summary>
		/// <param name="gameManager"> GameManagerのインスタンス </param>
		virtual void draw(const GameManager & gamaManager) const = 0;

	};
}