#pragma once


#include"../Load/LoadScene.h"


namespace Robot
{
	/*
	LoadEventSceneクラス
	イベントのデータのロードを行います。
	*/
	class LoadEventScene : public LoadScene
	{
	private:

		void load() override;

		void complete() override;

	};

}