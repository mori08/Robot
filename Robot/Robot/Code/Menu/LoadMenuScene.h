#pragma once


#include"../Load/LoadScene.h"


namespace Robot
{
	/*
	LoadMenuScene�N���X
	�Z�[�u�f�[�^���Q�Ƃ��Ȃ���
	���j���[�̃{�^�������[�h���܂��B
	*/
	class LoadMenuScene : public LoadScene
	{
	private:

		void load() override;

		void complete() override;

	};
}