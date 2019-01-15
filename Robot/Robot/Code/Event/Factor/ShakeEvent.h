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

	public:

		/// <summary>
		/// 画面の揺れを設定するイベント
		/// </summary>
		/// <param name="arg"> 引数の文字列の配列 </param>
		ShakeEvent(const std::vector<String> & arg);

	private:

		void perform(EventManager & eventManager) const override;

		bool isCompleted(const EventManager & eventManager) const override;

	};
}