#pragma once


#include "../EventManager.h"


namespace Robot
{
	/*
	ReloadEventクラス
	LoadEventSceneに遷移させ
	同じシーンを読み込みなおします
	*/
	class ReloadEvent : public EventBase
	{
	private:

		bool load(const Info & info, const EventManager &)override;

		void perform(EventManager & eventManager) const override;

		bool isCompleted(const EventManager &) const override;

	};
}