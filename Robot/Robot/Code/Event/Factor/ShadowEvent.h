#pragma once


#include "../EventManager.h"


namespace Robot
{
	/*
	ShadowEventクラス
	影の効果を付与します。
	*/
	class ShadowEvent : public EventBase
	{
	private:

		bool _shadow; // 影を付与するとき true , そうでないとき false

	private:

		bool load(const Info & info) override;

		void perform() const override;

		bool isCompleted() const override;

	};
}