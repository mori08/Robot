#pragma once


#include "../Load/LoadScene.h"


namespace Robot
{
	/*
	LoadDiarySceneクラス
	イベントのデータのロードを行います。
	シーン遷移先はMenuSceneにします
	*/
	class LoadDiaryScene : public LoadScene
	{
	private:

		void load() override;

		void complete() override;

	};
}