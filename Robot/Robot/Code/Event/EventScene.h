#pragma once


#include"../Main.h"


namespace Robot
{

	/*
	EventScene�N���X
	EventManager�œǂݍ��񂾓��e�����s���܂�
	*/
	class EventScene : public MyApp::Scene
	{
	private:

		String changeSceneName; // �J�ڐ�̃V�[����

	private:

		void init() override;

		void update() override;

		void draw() const override;

	};

}