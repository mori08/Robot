#pragma once


#include"../Load/LoadScene.h"
#include"SaveDataManager.h"
#include<thread>


namespace Robot
{
	/*
	LoadSaveDataScene�N���X
	�f�[�^�̃��[�h���s���܂��B
	�X���b�h�𑖂点SAVE-DATA.txt��ǂݍ��݂܂��B
	*/
	class LoadSaveDataScene : public LoadScene
	{
	private:

		SaveDataManager::LoadResult _loadResult; // ���[�h����

	private:

		void load() override;

		void complete() override;

	};
}