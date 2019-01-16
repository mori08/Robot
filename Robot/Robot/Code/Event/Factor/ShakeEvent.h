#pragma once


#include "../EventManager.h"


namespace Robot
{
	/*
	ShakeEventクラス
	EventManagerのsetShake関数を用いて
	画面の揺れを設定します
	*/
	class ShakeEvent : public EventBase
	{
	private:

		double _size; // 揺れの大きさ

		int    _span; // 揺れの長さ(フレーム数)

	private:

		bool load(const Info & info, const EventManager & eventManager) override;

		void perform(EventManager & eventManager) const override;

		bool isCompleted(const EventManager & eventManager) const override;

	};
}