#pragma once


#include "CentipedeEnemy.h"


namespace Robot
{
	/*
	DefenceCentipede�N���X
	�S�[���̎��ӂ�ǂ������܂�
	*/
	class DefenceCentipede : public CentipedeEnemy
	{
	private:

		Vec2 _goalPos;

	public:

		DefenceCentipede(const Vec2 & pos);

	private:

		Vec2 getGoalPos() override;

	};
}