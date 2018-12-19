#pragma once


#include"../Main.h"
#include"SaveDataManager.h"
#include<thread>


namespace Robot
{
	/*
	LoadDataSceneクラス
	データのロードを行います。
	スレッドを走らせSAVE-DATA.txtを読み込みます。
	*/
	class LoadDataScene : public MyApp::Scene
	{
	private:
		
		int         _frameCount; // 経過フレーム数

		bool        _isLoading;  // データをロード中のとき true , 終了したとき false

		std::thread _loadThread; // データをロードするスレッド

		SaveDataManager::LoadResult _loadResult; // ロード結果
		
	public:

		LoadDataScene();

		~LoadDataScene();

		void init() override;

		void update() override;

		void updateFadeIn(double) override;

		void updateFadeOut(double) override;

		void draw() const override;

		void drawFadeIn(double)const override;

		void drawFadeOut(double)const override;

	};
}