#pragma once


#include"../EventManager.h"


namespace Robot
{
	/*

	*/
	class InitEvent : public EventBase
	{
	private:

		void perform(EventManager &)const override
		{
		}

		bool isCompleted(const EventManager &)const override
		{
			return true;
		}

	};

}
