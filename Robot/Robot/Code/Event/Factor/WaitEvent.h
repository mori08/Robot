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

	public:

		/// <summary>
		/// 待機するイベント
		/// </summary>
		/// <param name="arg"> 引数の文字列の配列 </param>
		WaitEvent(const std::vector<String> & arg);

	private:

		void perform(EventManager & eventManager)const override;

		bool isCompleted(const EventManager & eventManager) const;

	};

}