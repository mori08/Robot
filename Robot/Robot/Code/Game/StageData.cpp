#include "StageData.h"


namespace
{
	const double SIDE_COST     = 1;       // 縦・横方向のコスト
	const double SLANTING_COST = Sqrt(2); // 斜め方向のコスト
}


void Robot::StageData::clear()
{
	// 地形のリセット
	for (int i = 0; i < N; ++i)
	{
		_terrain[i] = false;
	}

	// 経路のリセット
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			_path[i][j] = Vec2::Zero;
		}
	}
}


void Robot::StageData::searchPath()
{
	std::array<std::array<double, N>, N> distance; // 2点間の距離

	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			auto edge = getEdge(i, j);
			_path[i][j]    = edge.first;
			distance[i][j] = edge.second;
		}
	}

	for (int k = 0; k < N; ++k)
	{
		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j < N; ++j)
			{
				if (distance[i][j] > distance[i][k] + distance[k][j])
				{
					distance[i][j] = distance[i][k] + distance[k][j];
					_path[i][j]    = _path[i][k];
				}
			}
		}
	}
}


void Robot::StageData::draw() const
{
	for (int i = 0; i < N; ++i)
	{
		if (isWalkAble(i)) continue;

		Rect(SIZE*intToPoint(i), SIZE).draw(Palette::MyBlack);
	}
}


std::pair<Vec2, double> Robot::StageData::getEdge(int i, int j) const
{
	// 始点か終点が壁になるとき
	if (!isWalkAble(i) || !isWalkAble(j))
	{
		return { Vec2::Zero,Infinity<double>() }; // 辺なし
	}

	Point posI = intToPoint(i);
	Point posJ = intToPoint(j);
	Point sub  = posJ - posI;

	// 始点と終点が離れているとき
	if (Abs(sub.x) > 1 || Abs(sub.y) > 1)
	{
		return { Vec2::Zero,Infinity<double>() }; // 辺なし
	}

	// 始点と終点が同じ点であるとき
	if (Abs(sub.x) == 0 && Abs(sub.y) == 0)
	{
		return { Vec2::Zero,0 }; // コスト0
	}

	// 始点に対して終点がすぐ隣であるとき
	if (Abs(sub.x) == 0 || Abs(sub.y) == 0)
	{
		return { Vec2(sub.x,sub.y),SIDE_COST };
	}

	// 始点に対して終点がすぐ斜めにあるとき

	// その横に壁があるとき
	if (!isWalkAble(posI + Point(sub.x, 0)) || !isWalkAble(posI + Point(0, sub.y)))
	{
		return { Vec2::Zero,Infinity<double>() }; // 辺なし
	}

	return { Vec2(sub.x,sub.y).normalize(),SLANTING_COST };
}
