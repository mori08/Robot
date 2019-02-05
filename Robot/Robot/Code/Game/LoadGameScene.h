#pragma once


#include"../Load//LoadScene.h"


namespace Robot
{
	/*
	LoadGameSceneクラス
	ゲームデータのロードを行います。
	*/
	class LoadGameScene : public LoadScene
	{
	private:

		void load() override;

		void complete() override;

	};
}