#pragma once


#include "../EventManager.h"


namespace Robot
{
	/*
	MoveEventクラス
	EventObjectのsetLinerMove関数を用いて
	オブジェクトを移動させます。
	*/
	class MoveEvent : public EventBase
	{
	private:

		String _name;               // 動かすオブジェクトの名前

		// オブジェクトの移動が終わるまでisCompleted関数でfalseを返すなら true
		// そうでないなら false
		bool   _wait;

		int    _spanMoveFrameCount; // 移動にかかるフレーム数

		Point  _goal;               // 移動先

	private:

		bool load(const Info & info, const EventManager & eventManager) override;

		void perform(EventManager & eventManager) const override;

		bool isCompleted(const EventManager & eventManager) const override;

	};
}