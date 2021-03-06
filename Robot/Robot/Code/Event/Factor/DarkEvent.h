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

		bool load(const Info & info) override;

		void perform() const override;

		bool isCompleted() const override;

	};
}