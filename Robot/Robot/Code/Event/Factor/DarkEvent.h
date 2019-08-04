#pragma once


#include "../EventManager.h"


namespace Robot
{
	/*
	DarkEventƒNƒ‰ƒX
	ˆÃ“]‚µ‚Ü‚·B
	*/
	class DarkEvent : public EventBase
	{
	private:

		int  _darkAlpha;   // ˆÃ“]‚·‚é‚Æ‚« 255 , ‰ğœ‚·‚é‚Æ‚« 0

	private:

		bool load(const Info & info, const EventManager & eventManager)override;

		void perform(EventManager & eventManager) const override;

		bool isCompleted(const EventManager &) const override;

	};
}