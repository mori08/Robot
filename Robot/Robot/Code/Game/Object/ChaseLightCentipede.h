#pragma once


#include "CentipedeEnemy.h"


namespace Robot
{
	/*
	ChaseLightCentibete�N���X
	����ǐՂ��郀�J�f�^�̓G
	*/
	class ChaseLightCentipede : public CentipedeEnemy
	{
	public:

		ChaseLightCentipede(const Vec2 & pos);

	private:

		Vec2 getGoalPos() override;

	};
}