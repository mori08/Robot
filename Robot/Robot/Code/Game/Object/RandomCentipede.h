#pragma once


#include "CentipedeEnemy.h"


namespace Robot
{
	/*
	ChaseLightCentibete�N���X
	����ǐՂ��郀�J�f�^�̓G
	*/
	class RandomCentipede : public CentipedeEnemy
	{
	private:

		Vec2 _goalPos;

	public:

		RandomCentipede(const Vec2 & pos);

	private:

		Vec2 getGoalPos() override;

	};
}