#pragma once


#include "../MyLibrary.h"
#include "../Title/TitleLight.h"


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

		int                   _generateLightFrameCount;
		std::list<TitleLight> _lightList; // ���̃��X�g

	public:

		MenuScene();

	private:

		void update() override;

		void draw() const override;

	};
}