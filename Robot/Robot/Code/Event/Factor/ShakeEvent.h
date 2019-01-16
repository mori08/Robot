#pragma once


#include "../EventManager.h"


namespace Robot
{
	/*
	ShakeEventƒNƒ‰ƒX
	EventManager‚ÌsetShakeŠÖ”‚ğ—p‚¢‚Ä
	‰æ–Ê‚Ì—h‚ê‚ğİ’è‚µ‚Ü‚·
	*/
	class ShakeEvent : public EventBase
	{
	private:

		double _size; // —h‚ê‚Ì‘å‚«‚³

		int    _span; // —h‚ê‚Ì’·‚³(ƒtƒŒ[ƒ€”)

	private:

		bool load(const Info & info, const EventManager & eventManager) override;

		void perform(EventManager & eventManager) const override;

		bool isCompleted(const EventManager & eventManager) const override;

	};
}