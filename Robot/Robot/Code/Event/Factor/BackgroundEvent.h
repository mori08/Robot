#pragma once


#include"../EventManager.h"


namespace Robot
{
	/*
	BackgoundEventƒNƒ‰ƒX
	EventScene‚Ì”wŒi‚ð•ÏŠ·‚µ‚Ü‚·
	*/
	class BackgroundEvent : public EventBase
	{
	private:

		String _name; // ”wŒi‰æ‘œ‚Ì–¼‘O

	private:

		bool load(const Info & info) override;

		void perform() const override;

		bool isCompleted() const override;

	};

}