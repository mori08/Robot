#pragma once


#include "../EventManager.h"


namespace Robot
{
	/*
	MoveEvent�N���X
	EventObject��setLinerMove�֐���p����
	�I�u�W�F�N�g���ړ������܂��B
	*/
	class MoveEvent : public EventBase
	{
	private:

		String _name;               // �������I�u�W�F�N�g�̖��O

		// �I�u�W�F�N�g�̈ړ����I���܂�isCompleted�֐���false��Ԃ��Ȃ� true
		// �����łȂ��Ȃ� false
		bool   _wait;

		int    _spanMoveFrameCount; // �ړ��ɂ�����t���[����

		Point  _goal;               // �ړ���

	public:

		/// <summary>
		/// �I�u�W�F�N�g���ړ�����C�x���g
		/// </summary>
		/// <param name="arg"> �����̕�����̔z�� </param>
		MoveEvent(const std::vector<String> & arg);

	private:

		void perform(EventManager & eventManager) const override;

		bool isCompleted(const EventManager & eventManager) const override;

	};
}