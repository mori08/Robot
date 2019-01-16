#pragma once


#include"../EventManager.h"


namespace Robot
{
	/*
	BackgoundEventƒNƒ‰ƒX
	EventScene‚Ì”wŒi‚ğ•ÏŠ·‚µ‚Ü‚·
	*/
	class BackgroundEvent : public EventBase
	{
	private:

		String _name; // ”wŒi‰æ‘œ‚Ì–¼‘O

	private:

		bool load(const Info & info, const EventManager & eventManager)override;

		void perform(EventManager & eventManager) const override;

		bool isCompleted(const EventManager &) const override;

	};

}