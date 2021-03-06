#pragma once


#include<Siv3D.hpp>


namespace Robot
{
	/*
	StageDataクラス
	GameManagerで扱う地形の管理や
	経路探索を行います。
	*/
	class StageData
	{
	public:

		static const int WIDTH  = 16;           // ステージの幅(マス)
		static const int HEIGHT = 12;           // ステージの高さ(マス)
		static const int N      = WIDTH*HEIGHT; // マス目数
		static const int SIZE   = 40;           // １マスの大きさ(ピクセル)

	private:

		std::array<bool, N> _terrain;  // 地形 trueのとき障害物あり

		std::array<std::array<Vec2,    N>, N> _path;     // i→j への経路
		std::array<std::array<double , N>, N> _distance; // i→j への距離

	public:

		/// <summary>
		/// Vec2座標からマスを表現するPoint座標に変換します。
		/// </summary>
		/// <param name="pos"> Vec2座標 </param>
		/// <returns> マスを表現するPoint座標 </returns>
		static Point translatePos(const Vec2 & pos);

		/// <summary>
		/// マスの中心座標を取得します。
		/// </summary>
		/// <param name="pos"> マスを表現するPoint座標 </param>
		/// <returns> Vec2座標 </returns>
		static Vec2 centerPosOfCell(const Point & pos);

		/// <summary>
		/// 座標を示す整数値を座標に変換します。
		/// </summary>
		/// <param name="i"> 座標を示す整数値 </param>
		/// <returns> 座標 </returns>
		static Point intToPoint(int i)
		{
			return std::move(Point(i % WIDTH, i / WIDTH));
		}

		/// <summary>
		/// 座標をそれに対応する整数値に変換します。
		/// </summary>
		/// <param name="pos"> 座標 </param>
		/// <returns> 座標をしめす整数値 </returns>
		static int pointToInt(const Point & pos)
		{
			return pos.x + WIDTH*pos.y;
		}

	public:

		/// <summary>
		/// 示された座標が行動可能か示します。
		/// </summary>
		/// <param name="pos"> 座標 </param>
		/// <returns> 行動可能なとき true , 地図外であるときや壁があるとき false </returns>
		bool isWalkAble(const Point & pos) const
		{
			if (pos.x < 0 || pos.x >= WIDTH) return false;
			if (pos.y < 0 || pos.y >= HEIGHT)return false;
			return !_terrain[pointToInt(pos)];
		}

		/// <summary>
		/// 示された座標が行動可能か示します。
		/// </summary>
		/// <param name="x"> x座標 </param>
		/// <param name="y"> y座標 </param>
		/// <returns> 行動可能なとき true , 地図外であるときや壁があるとき false </returns>
		bool isWalkAble(int x, int y) const
		{
			return isWalkAble(Point(x, y));
		}

		/// <summary>
		/// 示された座標が行動可能か示します。
		/// </summary>
		/// <param name="i"> 座標を示す整数値 </param>
		/// <returns> 行動可能なとき true , 地図外であるときや壁があるとき false </returns>
		bool isWalkAble(int i) const
		{
			return isWalkAble(intToPoint(i));
		}

		/// <summary>
		/// 経路を取得します
		/// </summary>
		/// <param name="posS"> 始点 </param>
		/// <param name="posT"> 終点 </param>
		/// <returns> 経路上で最初に進む方向 行くことができない場合 Vec2::Zero </returns>
		Vec2 getPath(const Vec2 & posS, const Vec2 & posT) const;

		/// <summary>
		/// 距離を取得します
		/// </summary>
		/// <param name="posS"> 始点 </param>
		/// <param name="posT"> 終点 </param>
		/// <returns> 距離 </returns>
		double getDistance(const Vec2 & posS, const Vec2 & posT) const;


		/// <summary>
		/// 地形や経路の情報をリセットします。
		/// </summary>
		void clear();

		/// <summary>
		/// 壁を設置します。
		/// </summary>
		/// <param name="x"> x座標 </param>
		/// <param name="y"> y座標 </param>
		void setWall(int x, int y)
		{
			_terrain[pointToInt(Point(x, y))] = true;
		}

		/// <summary>
		/// ワーシャル・フロイド法を用いた経路探索を行います。
		/// </summary>
		void searchPath();

		/// <summary>
		/// ステージの描画
		/// </summary>
		void draw() const;

	private:

		/// <summary>
		/// 2頂点間の辺を取得します。
		/// </summary>
		/// <param name="i"> 始点を示す整数値 </param>
		/// <param name="j"> 終点を示す整数値 </param>
		/// <returns> 辺 { 方向,コスト } </returns>
		/// <remarks> 辺が存在しないとき { Vec2::Zero,INF } を返します。 </remarks>
		std::pair<Vec2, double> getEdge(int i, int j) const;

	};
}