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

	public:

		/// <summary>
		/// オブジェクトの演出を実行させるイベント
		/// </summary>
		/// <param name="arg"> 引数の文字列の配列 </param>
		ActEvent(const std::vector<String> & arg);

	private:

		void perform(EventManager & eventManager) const override;

		bool isCompleted(const EventManager & eventManager) const override;

	};
}