#pragma once


#include "../EventManager.h"


namespace Robot
{
	/*
	HideEventクラス
	指定したオブジェクトを非表示にする
	*/
	class HideEvent : public EventBase
	{
	private:

		String _name; // 非表示にするオブジェクトの名前

		bool   _hide; // true なら非表示に , false なら表示

	private:

		bool load(const Info & info) override;

		void perform() const override;

		bool isCompleted() const override;

	};
}