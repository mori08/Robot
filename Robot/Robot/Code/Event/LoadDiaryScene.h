#pragma once


#include "../Load/LoadScene.h"


namespace Robot
{
	/*
	LoadDiaryScene�N���X
	�C�x���g�̃f�[�^�̃��[�h���s���܂��B
	�V�[���J�ڐ��MenuScene�ɂ��܂�
	*/
	class LoadDiaryScene : public LoadScene
	{
	private:

		void load() override;

		void complete() override;

	};
}