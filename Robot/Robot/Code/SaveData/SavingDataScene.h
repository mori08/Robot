#pragma once


#include"../Load/LoadScene.h"


namespace Robot
{
	/*
	SavingDataScene�N���X
	�f�[�^�̃Z�[�u���s���܂��B
	�X���b�h�𑖂点SAVE-DATA.txt��ǂݍ��݂܂��B
	*/
	class SavingDataScene : public LoadScene
	{
	private:

		void load() override;

		void complete() override;

		void draw() const override;
	};
}