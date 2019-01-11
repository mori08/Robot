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

	public:

		/// <summary>
		/// ”wŒi‚ğ¶¬‚·‚éƒCƒxƒ“ƒg
		/// </summary>
		/// <param name="arg"> ˆø”‚Ì•¶š—ñ‚Ì”z—ñ </param>
		BackgroundEvent(const std::vector<String> & arg);

	private:

		void perform(EventManager & eventManager) const override;

		bool isCompleted(const EventManager &) const override;

	};

}