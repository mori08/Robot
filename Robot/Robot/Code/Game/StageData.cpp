#include "StageData.h"


namespace
{
	const double SIDE_COST     = 1;       // �c�E�������̃R�X�g
	const double SLANTING_COST = Sqrt(2); // �΂ߕ����̃R�X�g
}


void Robot::StageData::clear()
{
	// �n�`�̃��Z�b�g
	for (int i = 0; i < N; ++i)
	{
		_terrain[i] = false;
	}

	// �o�H�̃��Z�b�g
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
	std::array<std::array<double, N>, N> distance; // 2�_�Ԃ̋���

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
	// �n�_���I�_���ǂɂȂ�Ƃ�
	if (!isWalkAble(i) || !isWalkAble(j))
	{
		return { Vec2::Zero,Infinity<double>() }; // �ӂȂ�
	}

	Point posI = intToPoint(i);
	Point posJ = intToPoint(j);
	Point sub  = posJ - posI;

	// �n�_�ƏI�_������Ă���Ƃ�
	if (Abs(sub.x) > 1 || Abs(sub.y) > 1)
	{
		return { Vec2::Zero,Infinity<double>() }; // �ӂȂ�
	}

	// �n�_�ƏI�_�������_�ł���Ƃ�
	if (Abs(sub.x) == 0 && Abs(sub.y) == 0)
	{
		return { Vec2::Zero,0 }; // �R�X�g0
	}

	// �n�_�ɑ΂��ďI�_�������ׂł���Ƃ�
	if (Abs(sub.x) == 0 || Abs(sub.y) == 0)
	{
		return { Vec2(sub.x,sub.y),SIDE_COST };
	}

	// �n�_�ɑ΂��ďI�_�������΂߂ɂ���Ƃ�

	// ���̉��ɕǂ�����Ƃ�
	if (!isWalkAble(posI + Point(sub.x, 0)) || !isWalkAble(posI + Point(0, sub.y)))
	{
		return { Vec2::Zero,Infinity<double>() }; // �ӂȂ�
	}

	return { Vec2(sub.x,sub.y).normalize(),SLANTING_COST };
}
