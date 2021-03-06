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

		using Range = std::pair<Point, Point>;             // 移動の始点と終点

		using Act    = std::function<void()>;              // 演出用関数

		using ActPtr = std::shared_ptr<Act>;               // 演出用関数のポインタ

		using ActMap = std::unordered_map<String, ActPtr>; // 演出用関数のポインタのマップ

		static const ActPtr noAct; // 演出がないとき

	protected:

		Point  _pos;                // 座標

		Range  _moveRange;          // 移動の視点と終点

		int    _moveFrameCount;     // 移動時のフレーム数

		int    _spanMoveFrameCount; // 移動にかかるのフレーム数

		ActMap _initMap;            // オブジェクトの初期化用のマップ

		ActMap _actMap;             // 演出用の関数のマップ

		bool   _isActing;           // 演出時に true , そうでないとき false

		int    _actFrameCount;      // 演出時のフレーム数

		ActPtr _act;                // 演出

		bool   _isHidding;          // true のとき非表示

	public:

		/// <summary>
		/// イベントオブジェクト
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
			return !_isActing && _moveFrameCount > _spanMoveFrameCount;
		}

		/// <summary>
		/// 初期化関数が存在するか示します。
		/// </summary>
		/// <param name="name"> 初期化関数の名前 </param>
		/// <returns> 存在するとき true , そうでないとき false </returns>
		bool isExistedInit(const String & name) const
		{
			return _initMap.find(name) != _initMap.end();
		}

		/// <summary>
		/// 演出が存在するか示します。
		/// </summary>
		/// <param name="name"> 演出の名前 </param>
		/// <returns> 存在するとき true , そうでないとき false </returns>
		bool isExistedAct(const String & name) const
		{
			return _actMap.find(name) != _actMap.end();
		}

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="initName"> 初期化関数の名前 </param>
		void init(const String & initName);

		/// <summary>
		/// 演出を登録します。
		/// </summary>
		/// <param name="actName"> 演出の名前 </param>
		void setAct(const String & actName);

		/// <summary>
		/// 非表示・表示を切り替えます。
		/// </summary>
		/// <param name="hide"> true のとき 非表示 , false のとき 表示 </param>
		void setHide(bool hide)
		{
			_isHidding = hide;
		}

		/// <summary>
		/// 更新
		/// </summary>
		virtual void update();

		/// <summary>
		/// _isHidding を確認し、 true なら draw 関数を呼ぶ
		/// </summary>
		/// <param name="shakeSize"> 振動の大きさ </param>
		void checkHiddingAndDraw(const Vec2 & shakeSize) const;

	protected:

		/// <summary>
		/// 演出を終了します。
		/// </summary>
		void finishAct();

		/// <summary>
		/// 描画
		/// </summary>
		/// <param name="shakeSize"> 振動の大きさ </param>
		virtual void draw(const Vec2 & shakeSize) const = 0;

	private:

		/// <summary>
		/// オブジェクトを動かします。
		/// </summary>
		void moveObject();

	};
}