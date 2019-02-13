#pragma once


#include "GameManager.h"
#include "StageData.h"
#include "Object\GameObject.h"
#include "GameLight.h"


namespace
{
	// オブジェクトのリスト
	using ObjList = std::vector<std::unique_ptr<Robot::GameObject>>;
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

		StageData  _stageData; // ステージデータ

		ObjList    _objList;   // オブジェクトのリスト

		GameLight  _light;     // 光

		Vec2       _playerPos; // プレイヤーの座標

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
		/// 更新
		/// </summary>
		void update();

		/// <summary>
		/// 描画
		/// </summary>
		void draw() const;

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

	};
}