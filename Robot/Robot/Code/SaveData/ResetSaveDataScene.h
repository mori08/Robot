#pragma once


#include "../Load/LoadScene.h"


namespace Robot
{
	/*
	ResetSaveDataScene�N���X
	�Z�[�u�f�[�^�����Z�b�g���܂��B
	*/
	class ResetSaveDataScene : public LoadScene
	{
	private:

		void load() override;

		void complete() override;

	};
}