#pragma once


#include "CentipedeEnemy.h"


namespace Robot
{
	/*
	ChasePlayerCentibete�N���X
	�v���C���[��ǐՂ��郀�J�f�^�̓G
	*/
	class ChasePlayerCentipede : public CentipedeEnemy
	{
	public:

		ChasePlayerCentipede(const Vec2 & pos);

	private:

		Vec2 getGoalPos() override;

	};
}