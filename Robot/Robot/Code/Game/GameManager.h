#pragma once


namespace Robot
{
	/*
	GameManagerクラス
	CSVファイルからゲームデータを読み込み
	GameObject・GameLightの管理
	障害物の描画
	*/
	class GameManager
	{
	private:

	private:

		GameManager();

		GameManager(const GameManager &)             = default;
		GameManager & operator=(const GameManager &) = default;
		GameManager(GameManager &&)                  = default;
		GameManager & operator=(GameManager &&)      = default;

	public:

		/// <summary>
		/// シングルトンとして管理しているGameManagerのインスタンスを取得します。
		/// </summary>
		/// <returns> インスタンス </returns>
		static GameManager & Instance()
		{
			static GameManager gameManager;
			return gameManager;
		}

	};
}