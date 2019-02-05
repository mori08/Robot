#pragma once


#include "../Main.h"


namespace Robot
{
	/*
	GameSceneクラス
	GameManagerで読み込んだ内容を実行します。
	*/
	class GameScene : public MyApp::Scene
	{
	private:

		void update() override;

		void draw()const override;

	};
}