#pragma once


#include "../MyLibrary.h"
#include "MenuLight.h"


namespace Robot
{
	/*
	MenuSceneクラス
	ButtonListを管理し
	Menuを操作します
	*/
	class MenuScene : public MyApp::Scene
	{
	private:

		int                  _generateLightFrameCount;
		std::list<MenuLight> _lightList; // 光のリスト

	public:

		MenuScene();

	private:

		void update() override;

		void updateFadeOut(double) override;

		void draw() const override;

	};
}