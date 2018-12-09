#pragma once


#include"../Main.h"
#include"Light.h"


namespace Robot
{

	class TitleScene : public MyApp::Scene
	{
	private:

		int              _generateLightFrameCount; // 光を生成するまでのフレーム数
		std::list<Light> _lightList;               // 光のリスト

	public:

		TitleScene();

		void init() override;

		void update() override;

		void draw()const override;

	};

}