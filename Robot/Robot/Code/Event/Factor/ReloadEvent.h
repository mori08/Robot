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

		bool load(const Info & info) override;

		void perform() const override;

		bool isCompleted() const override;

	};
}