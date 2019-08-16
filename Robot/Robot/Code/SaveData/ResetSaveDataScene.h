#pragma once


#include "../Load/LoadScene.h"


namespace Robot
{
	/*
	ResetSaveDataSceneクラス
	セーブデータをリセットします。
	*/
	class ResetSaveDataScene : public LoadScene
	{
	private:

		void load() override;

		void complete() override;

	};
}