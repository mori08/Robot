#pragma once


#include"../GameManager.h"


namespace Robot
{
	/*
	TestGameObject�N���X
	�o�H�T����`�悪�������s���Ă��邩�e�X�g���܂��B
	*/
	class TestGameObject : public GameObject
	{
	public:

		TestGameObject();

	private:

		void update() override;

		void draw() const override;

	};
}