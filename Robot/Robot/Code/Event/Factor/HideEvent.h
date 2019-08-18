#pragma once


#include "../EventManager.h"


namespace Robot
{
	/*
	HideEvent�N���X
	�w�肵���I�u�W�F�N�g���\���ɂ���
	*/
	class HideEvent : public EventBase
	{
	private:

		String _name; // ��\���ɂ���I�u�W�F�N�g�̖��O

		bool   _hide; // true �Ȃ��\���� , false �Ȃ�\��

	private:

		bool load(const Info & info) override;

		void perform() const override;

		bool isCompleted() const override;

	};
}