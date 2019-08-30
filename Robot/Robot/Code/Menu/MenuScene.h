#pragma once


#include "../MyLibrary.h"
#include "MenuLight.h"


namespace Robot
{
	/*
	MenuScene�N���X
	ButtonList���Ǘ���
	Menu�𑀍삵�܂�
	*/
	class MenuScene : public MyApp::Scene
	{
	private:

		int _generateLightFrameCount;
		static std::list<MenuLight> _lightList; // ���̃��X�g

	public:

		MenuScene();

	private:

		void update() override;

		void updateFadeIn(double) override;

		void updateFadeOut(double) override;

		void draw() const override;

	};
}