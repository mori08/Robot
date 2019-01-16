#pragma once


#include"../EventManager.h"


namespace Robot
{
	/*
	WaitEventクラス
	指定されたフレーム数まで待機します
	*/
	class WaitEvent : public EventBase
	{
	private:

		int _waitFrameCount;  // 待機するフレーム数

		int _beginFrameCount; // 待機を開始したフレーム数

	private:

		bool load(const Info & info, const EventManager&eventManager) override;

		void perform(EventManager & eventManager) const override;

		bool isCompleted(const EventManager & eventManager) const;

	};

}