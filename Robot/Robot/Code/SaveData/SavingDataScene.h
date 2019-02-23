#pragma once


#include"../Load/LoadScene.h"


namespace Robot
{
	/*
	SavingDataSceneクラス
	データのセーブを行います。
	スレッドを走らせSAVE-DATA.txtを読み込みます。
	*/
	class SavingDataScene : public LoadScene
	{
	private:

		void load() override;

		void complete() override;

		void draw() const override;
	};
}