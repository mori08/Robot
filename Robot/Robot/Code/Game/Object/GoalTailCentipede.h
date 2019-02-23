#pragma once


#include "CentipedeEnemy.h"


namespace Robot
{
	/*
	GoalTailCentipede�N���X
	�K�����S�[���ɂȂ��Ă��郀�J�f�^�̓G
	*/
	class GoalTailCentipede : public CentipedeEnemy
	{
	private:

		bool _topOrBottom; // ��Ɍ������Ƃ� true , �����łȂ��Ƃ� false
		Vec2 _goalPos;

	public:

		GoalTailCentipede(const Vec2 & pos);

	private:

		Vec2 getGoalPos() override;

	};
}