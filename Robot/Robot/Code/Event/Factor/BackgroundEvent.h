#pragma once


#include"../EventManager.h"


namespace Robot
{
	/*
	BackgoundEvent�N���X
	EventScene�̔w�i��ϊ����܂�
	*/
	class BackgroundEvent : public EventBase
	{
	private:

		String _name; // �w�i�摜�̖��O

	private:

		bool load(const Info & info, const EventManager & eventManager)override;

		void perform(EventManager & eventManager) const override;

		bool isCompleted(const EventManager &) const override;

	};

}