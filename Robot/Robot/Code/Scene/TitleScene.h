#pragma once


#include"../Main.h"


namespace Robot
{

	class TitleScene : MyApp::Scene
	{
	private:


	public:

		TitleScene();

		void init() override;

		void update() override;

		void draw()const override;

	};

}