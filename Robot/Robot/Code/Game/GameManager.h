#pragma once


#include <Siv3D.hpp>
#include "StageData.h"


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

		StageData _stageData; // ステージデータ

	private:

		GameManager()
		{

		}

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

	private:

		/// <summary>
		/// エラーメッセージを出力します。
		/// </summary>
		/// <param name="message"> メッセージ </param>
		static void printError(const String & message)
		{
#ifdef _DEBUG
			Println(message);
#endif // _DEBUG
		}

	public: // GameSceneで使用する関数

		/// <summary>
		/// ゲームデータを記述したcsvファイルを読み込みます。
		/// </summary>
		/// <param name="gameDataFileName"> csvファイルの名前 </param>
		void load(const String & gameDataFileName);

		/// <summary>
		/// 描画
		/// </summary>
		void draw() const;

	};
}