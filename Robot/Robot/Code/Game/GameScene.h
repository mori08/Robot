#pragma once


#include "../Main.h"


namespace Robot
{
	/*
	GameScene�N���X
	GameManager�œǂݍ��񂾓��e�����s���܂��B
	*/
	class GameScene : public MyApp::Scene
	{
	private:

		String changeSceneName; // �J�ڐ�̃V�[����

	private:

		void update() override;

		void draw()const override;

	};
}