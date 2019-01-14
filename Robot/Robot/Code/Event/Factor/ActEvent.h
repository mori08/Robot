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

	public:

		/// <summary>
		/// �I�u�W�F�N�g�̉��o�����s������C�x���g
		/// </summary>
		/// <param name="arg"> �����̕�����̔z�� </param>
		ActEvent(const std::vector<String> & arg);

	private:

		void perform(EventManager & eventManager) const override;

		bool isCompleted(const EventManager & eventManager) const override;

	};
}