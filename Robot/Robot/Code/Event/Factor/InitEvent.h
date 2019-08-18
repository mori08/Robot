#pragma once


#include"../EventManager.h"


namespace Robot
{
	/*
	InitEvent�N���X
	�I�u�W�F�N�g�̏��������s���܂��B
	Run���߂��O�Ɏg�p����
	*/
	class InitEvent : public EventBase
	{
	private:

		String _objectName; // �I�u�W�F�N�g�̖��O

		String _initName;   // �������֐��̖��O

	private:

		bool load(const Info & info) override;

		void perform() const override;

		bool isCompleted() const override;

	};
}