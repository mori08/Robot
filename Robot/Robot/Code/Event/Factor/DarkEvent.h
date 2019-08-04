#pragma once


#include "../EventManager.h"


namespace Robot
{
	/*
	DarkEvent�N���X
	�Ó]���܂��B
	*/
	class DarkEvent : public EventBase
	{
	private:

		int  _darkAlpha;   // �Ó]����Ƃ� 255 , ��������Ƃ� 0

	private:

		bool load(const Info & info, const EventManager & eventManager)override;

		void perform(EventManager & eventManager) const override;

		bool isCompleted(const EventManager &) const override;

	};
}