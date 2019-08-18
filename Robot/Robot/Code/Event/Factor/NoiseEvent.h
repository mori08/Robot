#pragma once


#include "../EventManager.h"


namespace Robot
{
	/*
	NoiseEventクラス
	画面にノイズ(ゲームオーバー演出のようなもの)を
	指定された時間表示する
	*/
	class NoiseEvent : public EventBase
	{
	private:

		bool _noise; // true のとき ノイズの付与

	private:

		bool load(const Info & info) override;

		void perform() const override;

		bool isCompleted() const override;

	};
}