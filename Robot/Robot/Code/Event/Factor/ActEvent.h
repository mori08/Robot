#pragma once


#include "../EventManager.h"


namespace Robot
{
	/*
	ActEventクラス
	EventObjectのsetAct関数を用いて
	演出を実行させます。
	*/
	class ActEvent : public EventBase
	{
	private:

		String _objectName; // オブジェクトの名前

		String _actName;    // 演出の名前

	private:

		bool load(const Info & info) override;

		void perform() const override;

		bool isCompleted() const override;

	};
}