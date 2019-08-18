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

		bool load(const Info & info) override;

		void perform() const override;

		bool isCompleted() const override;

	};
}