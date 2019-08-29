#pragma once


#include "../MyLibrary.h"
#include "../Title/TitleLight.h"


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

		int                   _generateLightFrameCount;
		std::list<TitleLight> _lightList; // 光のリスト

	public:

		MenuScene();

	private:

		void update() override;

		void draw() const override;

	};
}