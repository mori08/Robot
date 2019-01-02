#pragma once


#include "../Main.h"
#include <thread>


namespace Robot
{
	/*
	LoadSceneクラス
	時間のかかる処理を別スレッドで行います。

	*/
	class LoadScene : public MyApp::Scene
	{
	private:

		bool _isLoading;  // ロード中のとき true , 終了したとき false

		int  _frameCount; // 経過フレーム数

	protected:

		std::thread _loadThread; // ロードするスレッド

	public:

		LoadScene();

		virtual ~LoadScene();

	public:

		void init() override;

		void update() override;

		void updateFadeIn(double) override;

		void updateFadeOut(double) override;

		void draw() const override;

		void drawFadeIn(double) const override;

		void drawFadeOut(double) const override;

	protected:

		/// <summary>
		/// _loadThreadで動かす関数
		/// </summary>
		virtual void load() = 0;

		/// <summary>
		/// スレッドの処理が終了したときに行う処理
		/// </summary>
		/// <remarks> 
		/// 必ずchangeScene関数を用いてScene遷移を行うこと 
		/// </remarks>
		virtual void complete() = 0;

	};

}