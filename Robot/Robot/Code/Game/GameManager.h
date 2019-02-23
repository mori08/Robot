#pragma once


#include "StageData.h"
#include "Object\GameObject.h"
#include "State\GameState.h"
#include "GameLight.h"


namespace
{
	// オブジェクトのポインタ
	using ObjPtr = std::unique_ptr<Robot::GameObject>;

	// オブジェクトのリスト
	using ObjList = std::vector<ObjPtr>;

	// オブジェクトを生成する関数
	using GenerateFunc = std::function<ObjPtr(const Vec2 & pos)>;

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

		// オブジェクトを生成する関数のマップ
		using FuncMap = std::unordered_map<String, GenerateFunc>;

	private:

		static FuncMap genarateEnemyMap; // オブジェクトを生成する関数のマップ

	private:

		String     _stageName; // ステージ名

		StatePtr   _gameState; // 状態

		StageData  _stageData; // ステージデータ

		ObjList    _objList;   // オブジェクトのリスト

		GameLight  _light;     // 光

		Vec2       _playerPos; // プレイヤーの座標

		Vec2       _goalPos;   // ゴールの座標

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

		/// <summary>
		/// GameObjectを生成する関数を登録します。
		/// </summary>
		static void setObjMap();

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
		/// 型名gameObjectTypeのunique_ptrを作る関数をマップに登録します。
		/// </summary>
		/// <param name="name"> オブジェクトの名前 </param>
		template<typename gameObjectType>
		static void makeGenerateFunc(const String & name)
		{
			genarateEnemyMap[name] = GenerateFunc
			(
				[](const Vec2 & pos)
				{
					return std::make_unique<gameObjectType>(pos);
				}
			);
		}

		/// <summary>
		/// 指定された行から座標を取得します。
		/// </summary>
		/// <param name="csvReader"> CSVReader </param>
		/// <param name="readingRow"> 指定する行 </param>
		/// <returns> 座標のOptional </returns>
		Optional<Vec2> getPointFromCSVReader(const CSVReader & csvReader, size_t readingRow);

		/// <summary>
		/// 初期化
		/// </summary>
		void init();

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
		/// ステージ名を設定します
		/// </summary>
		void setStageName(const String & name)
		{
			_stageName = name;
		}

		/// <summary>
		/// ステージ名を取得します
		/// </summary>
		const String & getStageName() const
		{
			return _stageName;
		}

		/// <summary>
		/// オブジェクトと光の更を行います。
		/// </summary>
		void updateObjectAndLight();

		/// <summary>
		/// オブジェクトと光の描画を行います。
		/// </summary>
		void drawObjectAndLight()const;

		/// <summary>
		/// gameStateを変更します。
		/// </summary>
		/// <param name="gameState"> gameStateのunique_ptr </param>
		void changeGameState(StatePtr gameState)
		{
			_gameState = std::move(gameState);
		}

		/// <summary>
		/// シーンの設定先を設定します。
		/// </summary>
		void setSceneName(const String & sceneName, const String & sceneInfo);

		/// <summary>
		/// チュートリアル用のゴールを作成します。
		/// </summary>
		void makeTutorialGoal();

	public: // GameObjectで使用する関数

		/// <summary>
		/// 経路を取得します。
		/// </summary>
		/// <param name="posS"> 始点 </param>
		/// <param name="posT"> 終点 </param>
		/// <returns> 経路上で最初に進む方向 </returns>
		Vec2 getPath(const Vec2 & posS, const Vec2 & posT) const
		{
			return _stageData.getPath(posS, posT);
		}

		/// <summary>
		/// 2点間の距離を取得します。
		/// </summary>
		/// <param name="posS"> 始点 </param>
		/// <param name="posT"> 終点 </param>
		/// <returns> 距離 </returns>
		double getDistance(const Vec2 & posS, const Vec2 & posT) const
		{
			return _stageData.getDistance(posS, posT);
		}

		/// <summary>
		/// 示された座標が行動可能か示します．
		/// </summary>
		/// <param name="pos"> 座標 </param>
		/// <returns> 行動可能なとき true , そうでないとき false </returns>
		bool isWalkingAblePos(const Vec2 & pos) const
		{
			if (pos.x < 0 || pos.y < 0) { return false; }
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
		/// ゴールの座標を設定します。
		/// </summary>
		/// <param name="goalPos"> ゴールの座標 </param>
		void setGoalPos(const Vec2 & goalPos)
		{
			_goalPos = goalPos;
		}

		/// <summary>
		/// ゴールの座標を取得します。
		/// </summary>
		/// <returns> ゴールの座標 </returns>
		const Vec2 & getGoalPos() const
		{
			return _goalPos;
		}

		/// <summary>
		/// 光の中心座標を設定します。
		/// </summary>
		/// <param name="pos"> 光の中心座標 </param>
		void setLightPos(const Vec2 & pos)
		{
			_light.setPos(pos);
		}

		/// <summary>
		/// 光の中心座標を取得します。
		/// </summary>
		const Vec2 & getLightPos() const
		{
			return _light.getPos();
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