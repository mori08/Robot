#pragma once


#include "../EventManager.h"


namespace Robot
{
	/*
	DarkEventクラス
	暗転します。
	*/
	class DarkEvent : public EventBase
	{
	private:

		int  _darkAlpha;   // 暗転するとき 255 , 解除するとき 0

	private:

		bool load(const Info & info, const EventManager & eventManager)override;

		void perform(EventManager & eventManager) const override;

		bool isCompleted(const EventManager &) const override;

	};
}