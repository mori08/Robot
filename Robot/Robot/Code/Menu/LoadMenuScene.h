#pragma once


#include"../Load/LoadScene.h"


namespace Robot
{
	/*
	LoadMenuSceneクラス
	セーブデータを参照しながら
	メニューのボタンをロードします。
	*/
	class LoadMenuScene : public LoadScene
	{
	private:

		void load() override;

		void complete() override;

	};
}