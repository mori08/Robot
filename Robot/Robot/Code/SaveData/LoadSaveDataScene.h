#pragma once


#include"../Load/LoadScene.h"
#include"SaveDataManager.h"
#include<thread>


namespace Robot
{
	/*
	LoadSaveDataSceneクラス
	データのロードを行います。
	スレッドを走らせSAVE-DATA.txtを読み込みます。
	*/
	class LoadSaveDataScene : public LoadScene
	{
	private:

		SaveDataManager::LoadResult _loadResult; // ロード結果

	private:

		void load() override;

		void complete() override;

	};
}