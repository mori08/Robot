#pragma once


#include "../EventManager.h"


namespace Robot
{
	/*
	ActEvent�N���X
	EventObject��setAct�֐���p����
	���o�����s�����܂��B
	*/
	class ActEvent : public EventBase
	{
	private:

		String _objectName; // �I�u�W�F�N�g�̖��O

		String _actName;    // ���o�̖��O

	private:

		bool load(const Info & info) override;

		void perform() const override;

		bool isCompleted() const override;

	};
}