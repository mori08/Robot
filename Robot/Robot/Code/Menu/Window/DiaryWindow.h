#pragma once


#include "../MenuScene.h"


namespace Robot
{
	/*
	DiaryWindow�N���X
	�C�x���g�̍ēǂݍ���
	*/
	class DiaryWindow : public MenuWindowBase
	{
	private:

		int _stageNum;

	public:

		DiaryWindow(MenuScene & menuScene);

	private:

		void draw() const override;

		void updateInputManager() const override;

	};
}