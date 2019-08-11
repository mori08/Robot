#pragma once


#include "../EventManager.h"


namespace Robot
{
	/*
	ReloadEvent�N���X
	LoadEventScene�ɑJ�ڂ���
	�����V�[����ǂݍ��݂Ȃ����܂�
	*/
	class ReloadEvent : public EventBase
	{
	private:

		bool load(const Info & info, const EventManager &)override;

		void perform(EventManager & eventManager) const override;

		bool isCompleted(const EventManager &) const override;

	};
}