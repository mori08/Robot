#pragma once

#include<Siv3D.hpp>

namespace Robot
{
	/*
	EventObjectクラス
	Eventシーンで使用するObject
	描画・移動・その他アクションを実装する

	このクラスの派生クラスを作るときは
	GenerateObjectのsetObjectMap関数に登録する
	*/
	class EventObject
	{
	protected:

		using Range = std::pair<Point, Point>;

		using Act = std::shared_ptr<std::function<void()>>;

		using ActMap = std::unordered_map<String, Act>;

		static const Act noAct; // 演出がないとき

	protected:

		Point  _pos;                // 座標

		Range  _moveRange;          // 移動の視点と終点

		int    _moveFrameCount;     // 移動時のフレーム数

		int    _spanMoveFrameCount; // 移動にかかるのフレーム数

		ActMap _actMap;             // 演出用の関数のマップ

		bool   _isActing;           // 演出時に true , そうでないとき false

		int    _actFrameCount;      // 演出時のフレーム数

		Act    _act;                // 演出

	public:

		/// <summary>
		/// EventObjectを生成します。
		/// </summary>
		/// <param name="pos"> 座標 </param>
		EventObject(const Point & pos);

		/// <summary>
		/// オブジェクトの移動を設定します。
		/// </summary>
		/// <param name="goal"> 移動先の座標 </param>
		/// <param name="spanFrameCount"> 移動にかかるフレーム数 (0のときはすぐ移動) </param>
		void setLinearMove(const Point & goal, int spanFrameCount = 0);

		/// <summary>
		/// 移動と演出が終了しているか示します。
		/// </summary>
		/// <returns> 終了しているとき true , そうでないとき false </returns>
		bool completeMoveAndAct() const
		{
			return _isActing && _moveFrameCount > _spanMoveFrameCount;
		}

		/// <summary>
		/// 演出を登録します。
		/// </summary>
		/// <param name="actName"> 演出の名前 </param>
		void setAct(const String & actName);

		/// <summary>
		/// 更新
		/// </summary>
		virtual void update();

		/// <summary>
		/// 描画
		/// </summary>
		virtual void draw() const = 0;

	private:

		/// <summary>
		/// オブジェクトを動かします。
		/// </summary>
		void moveObject();

	};
}