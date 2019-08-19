#pragma once


#include "GameGoal.h"


namespace Robot
{
	/*
	RunAwayGoal�N���X
	�v���C���[���瓦����S�[��
	*/
	class RunAwayGoal : public GameGoal
	{
	private:

		std::vector<Point> _runPointList; // �������W���X�g
		int                _goalPointId;  // �ړI���W

	public:

		RunAwayGoal(const Vec2 & pos);

	private:

		Vec2 getMoveVec() override;

	};
}