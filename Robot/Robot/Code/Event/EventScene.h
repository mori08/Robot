#pragma once


#include"../MyLibrary.h"


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

		void updateFadeIn(double) override;

		void updateFadeOut(double) override;

		void draw() const override;

	};

}