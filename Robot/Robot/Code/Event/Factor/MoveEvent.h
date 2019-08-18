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

	private:

		bool load(const Info & info) override;

		void perform() const override;

		bool isCompleted() const override;

	};
}