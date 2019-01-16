#pragma once


#include"../EventManager.h"


namespace Robot
{
	/*
	InitEventクラス
	空のイベント
	キューの最初に入れておく
	*/
	class InitEvent : public EventBase
	{
	public:

		InitEvent()
		{
			_isSuccess = true;
		}

	private:

		bool load(const Info &, const EventManager &) override
		{
			return true;
		}

		void perform(EventManager &)const override
		{
		}

		bool isCompleted(const EventManager &)const override
		{
			return true;
		}

	};

}
