#pragma once


#include"../Load/LoadScene.h"


namespace Robot
{
	/*
	LoadEventScene�N���X
	�C�x���g�̃f�[�^�̃��[�h���s���܂��B
	*/
	class LoadEventScene : public LoadScene
	{
	private:

		void load() override;

		void complete() override;

	};

}