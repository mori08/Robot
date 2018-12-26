#pragma once

#include<Siv3D.hpp>

namespace Robot
{
	/*
	EventObjectクラス
	Eventシーンで使用するObject
	描画・移動・その他アクションを実装する
	*/
	class EventObject
	{
	protected:

		using Range = std::pair<Point, Point>;

		using Act = std::shared_ptr<std::function<void()>>;

		using ActMap = std::unordered_map<String, Act>;

	protected:

		Point  _pos;                // 座標

		Range  _moveRange;          // 移動の視点と終点

		bool   _isActing;           // 演出時に true , そうでないとき false

		Act    _act;                // 演出

		int    _moveFrameCount;     // 移動時のフレーム数

		int    _spanMoveFrameCount; // 移動にかかるのフレーム数

		ActMap _actMap;             // 演出用の関数のマップ

	public:

		/// <summary>
		/// オブジェクトの移動を設定します。
		/// </summary>
		/// <param name="pos"> 移動先の座標 </param>
		/// <param name="spanFrameCount"> 移動にかかるフレーム数 </param>
		void setLinearMove(const Point & pos, int spanFrameCount);

		bool CompleteMoving() const
		{
			return _moveFrameCount > _spanMoveFrameCount;
		}

		/// <summary>
		/// 演出を登録します。
		/// </summary>
		/// <param name="actName"> 演出の名前 </param>
		void setAct(const String & actName);

		/// <summary>
		/// 更新
		/// </summary>
		void update();

		/// <summary>
		/// 描画
		/// </summary>
		void draw() const;

	};
}