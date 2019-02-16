#pragma once


#include"../GameManager.h"


namespace Robot
{
	/*
	GameGaol�N���X
	Player�����̃I�u�W�F�N�g�ɐG�ꂽ��
	�N���A�ƂȂ�܂��B
	*/
	class GameGoal : public GameObject
	{
	public:

		/// <summary>

		GameGoal(const Vec2 & pos)
			: GameObject(pos)
		{

		}

	private:

		void update(GameManager & gameManager) override;

		void draw() const override;

	};
}