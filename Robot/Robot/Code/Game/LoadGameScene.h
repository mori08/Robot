#pragma once


#include"../Load//LoadScene.h"


namespace Robot
{
	/*
	LoadGameScene�N���X
	�Q�[���f�[�^�̃��[�h���s���܂��B
	*/
	class LoadGameScene : public LoadScene
	{
	private:

		void load() override;

		void complete() override;

	};
}