#pragma once


#include "MenuWindowBase.h"


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

		DiaryWindow();

	private:

		void draw() const override;

		void updateInputManager() const override;

		void makeButton() override;

	};
}