#pragma once


#include "StageData.h"
#include "Object\GameObject.h"
#include "State\GameState.h"
#include "GameLight.h"


namespace
{
	// オブジェクトのリスト
	using ObjList = std::vector<std::unique_ptr<Robot::GameObject>>;

	// 状態のポインタ
	using StatePtr = std::unique_ptr<Robot::GameState>;
}


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

		StatePtr   _gameState; // 状態

		StageData  _stageData; // ステージデータ

		ObjList    _objList;   // オブジェクトのリスト

		GameLight  _light;     // 光

		Vec2       _playerPos; // プレイヤーの座標

		bool       _isChangeAbleScene; // シーン遷移可能か

		String     _sceneName; // シーン名

		String     _sceneInfo; // シーンの遷移先の補足

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

		/// <summary>
		/// 指定された行から座標を取得します。
		/// </summary>
		/// <param name="csvReader"> CSVReader </param>
		/// <param name="readingRow"> 指定する行 </param>
		/// <returns> 座標のOptional </returns>
		Optional<Point> getPointFromCSVReader(const CSVReader & csvReader, size_t readingRow);

	public: // GameSceneで使用する関数

		/// <summary>
		/// ゲームデータを記述したcsvファイルを読み込みます。
		/// </summary>
		/// <param name="gameDataFileName"> csvファイルの名前 </param>
		void load(const String & gameDataFileName);

		/// <summary>
		/// 更新
		/// </summary>
		void update();

		/// <summary>
		/// 描画
		/// </summary>
		void draw() const;

		/// <summary>
		/// シーン遷移先を代入して、シーン遷移が可能か示します。
		/// </summary>
		/// <param name="sceneName"> シーンの名前 </param>
		/// <param name="sceneInfo"> 遷移先での補足情報 </param>
		/// <returns> 遷移可能なとき true , そうでないとき false </returns>
		bool isChangeAbleScene(String & sceneName, String & sceneInfo) const;

	public: // GameStateで使用する関数

		/// <summary>
		/// オブジェクトと光の更を行います。
		/// </summary>
		void updateObjectAndLight();

		/// <summary>
		/// オブジェクトと光の描画を行います。
		/// </summary>
		void drawObjectAndLight()const;

		/// <summary>
		/// シーンの設定先を設定します。
		/// </summary>
		void setSceneName(const String & sceneName, const String & sceneInfo);

	public: // GameObjectで使用する関数

		/// <summary>
		/// 経路を取得します。
		/// </summary>
		/// <param name="posS"> 始点 </param>
		/// <param name="posT"> 終点 </param>
		/// <returns> 経路上で最初に進む方向 </returns>
		const Vec2 & getPath(const Vec2 & posS, const Vec2 & posT) const
		{
			return _stageData.getPath(posS, posT);
		}

		/// <summary>
		/// 示された座標が行動可能か示します．
		/// </summary>
		/// <param name="pos"> 座標 </param>
		/// <returns> 行動可能なとき true , そうでないとき false </returns>
		bool isWalkingAblePos(const Vec2 & pos) const
		{
			return _stageData.isWalkAble(pos.asPoint() / _stageData.SIZE);
		}

		/// <summary>
		/// プレイヤーの座標を設定します。
		/// </summary>
		/// <param name="playerPos"> プレイヤーの座標 </param>
		void setPlayerPos(const Vec2 & playerPos)
		{
			_playerPos = playerPos;
		}

		/// <summary>
		/// プレイヤーの座標を取得します。
		/// </summary>
		const Vec2 & getPlayerPos() const
		{
			return _playerPos;
		}

		/// <summary>
		/// ゲームクリア
		/// </summary>
		void gameClear();

		/// <summary>
		/// ゲームオーバー
		/// </summary>
		void gameOver();

	};
}