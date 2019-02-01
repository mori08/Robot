#pragma once


#include"../Main.h"


namespace Robot
{

	/*
	EventSceneクラス
	EventManagerで読み込んだ内容を実行します
	*/
	class EventScene : public MyApp::Scene
	{
	private:

		String changeSceneName; // 遷移先のシーン名

	private:

		void init() override;

		void update() override;

		void updateFadeIn(double) override;

		void updateFadeOut(double) override;

		void draw() const override;

	};

}