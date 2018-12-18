#pragma once


#include"../Main.h"
#include"SaveDataManager.h"
#include<thread>


namespace Robot
{
	/*
	LoadDataScene�N���X
	�f�[�^�̃��[�h���s���܂��B
	�X���b�h�𑖂点SAVE-DATA.txt��ǂݍ��݂܂��B
	*/
	class LoadDataScene : public MyApp::Scene
	{
	private:
		
		bool        _isLoading;  // �f�[�^�����[�h���̂Ƃ� true , �I�������Ƃ� false

		std::thread _loadThread; // �f�[�^�����[�h����X���b�h

		SaveDataManager::LoadResult _loadResult; // ���[�h����
		
	public:

		LoadDataScene();

		~LoadDataScene();

		void init() override;

		void update() override;

		void draw() const override;
	};
}