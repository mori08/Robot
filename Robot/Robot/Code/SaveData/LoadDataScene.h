#pragma once


#include"../Main.h"


namespace Robot
{
	/*
	LoadDataSceneクラス
	データのロードを行います。
	スレッドを走らせSAVE-DATA.txtを読み込みます。
	*/
	class LoadDataScene : MyApp::Scene
	{
	private:


	public:

		LoadDataScene();

		~LoadDataScene();

		void init() override;

		void update() override;

		void draw() const override;
	};
}