#pragma once


#include"../Main.h"


namespace Robot
{
	/*
	LoadDataScene�N���X
	�f�[�^�̃��[�h���s���܂��B
	�X���b�h�𑖂点SAVE-DATA.txt��ǂݍ��݂܂��B
	*/
	class LoadDataScene : MyApp::Scene
	{
	private:


	public:

		LoadDataScene();

		~LoadDataScene();

		void init() override;

		void update() override;

		void draw() const override;
	};
}