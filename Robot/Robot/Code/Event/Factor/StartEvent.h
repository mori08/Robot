#pragma once


#include"../EventManager.h"


namespace Robot
{
	/*
	StartEventクラス
	空のイベント
	キューの最初に入れておく
	*/
	class StartEvent : public EventBase
	{
	public:

		StartEvent()
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
