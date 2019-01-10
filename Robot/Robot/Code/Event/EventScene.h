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

		void init() override;

		void update() override;

		void draw() const override;

	};

}