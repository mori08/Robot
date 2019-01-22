#pragma once


#include "../EventManager.h"


namespace Robot
{
	/*
	ShadowEventƒNƒ‰ƒX
	‰e‚ÌŒø‰Ê‚ğ•t—^‚µ‚Ü‚·B
	*/
	class ShadowEvent : public EventBase
	{
	private:

		bool _shadow; // ‰e‚ğ•t—^‚·‚é‚Æ‚« true , ‚»‚¤‚Å‚È‚¢‚Æ‚« false

	private:

		bool load(const Info & info, const EventManager &) override;

		void perform(EventManager & eventManager) const override;

		bool isCompleted(const EventManager &) const override;

	};
}