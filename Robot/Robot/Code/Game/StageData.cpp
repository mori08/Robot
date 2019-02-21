#include "StageData.h"


namespace
{
	const double SIDE_COST     = 1;       // �c�E�������̃R�X�g
	const double SLANTING_COST = Sqrt(2); // �΂ߕ����̃R�X�g

	const double MIN_LENGTH=1.0; // �o�H�T�����s���ŏ��̋��� 
}


Point Robot::StageData::translatePos(const Vec2 & pos)
{
	int x = pos.x < 0 ? -1 : (pos.asPoint().x / SIZE);
	int y = pos.y < 0 ? -1 : (pos.asPoint().y / SIZE);
	return Point(x, y);
}


Vec2 Robot::StageData::centerPosOfCell(const Point & pos)
{
	return SIZE*Vec2::One*pos + Vec2::One / 2;
}


const Vec2 & Robot::StageData::getPath(const Vec2 & posS, const Vec2 & posT) const
{
	if (!isWalkAble(posS.asPoint() / SIZE) || !isWalkAble(posT.asPoint() / SIZE) || (posT-posS).length() < MIN_LENGTH)
	{
		return Vec2::Zero;
	}

	int s = pointToInt(posS.asPoint() / SIZE);
	int t = pointToInt(posT.asPoint() / SIZE);

	if (s == t)
	{
		return (posT - posS).normalize();
	}

	return _path[s][t];
}


double Robot::StageData::getDistance(const Vec2 & posS, const Vec2 & posT) const
{
	Point pS = translatePos(posS);
	Point pT = translatePos(posT);

	if (!isWalkAble(pS) || !isWalkAble(pT))
	{
		return Infinity<double>();
	}
	return _distance[pointToInt(pS)][pointToInt(pT)];
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
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			auto edge = getEdge(i, j);
			_path[i][j]     = edge.first;
			_distance[i][j] = edge.second;
		}
	}

	for (int k = 0; k < N; ++k)
	{
		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j < N; ++j)
			{
				if (_distance[i][j] > _distance[i][k] + _distance[k][j])
				{
					_distance[i][j] = _distance[i][k] + _distance[k][j];
					_path[i][j]     = _path[i][k];
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
