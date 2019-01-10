#pragma once


#include"../EventManager.h"


namespace Robot
{
	/*
	BackgoundEventクラス
	EventSceneの背景を変換します
	*/
	class BackgroundEvent : public EventBase
	{
	private:

		String _name; // 背景画像の名前

	public:

		/// <summary>
		/// 背景を生成するイベントを生成します。
		/// </summary>
		/// <param name="arg"> 引数の文字列の配列 </param>
		BackgroundEvent(const std::vector<String> & arg);

	private:

		void perform(EventManager & eventManager) const override;

		bool isCompleted(const EventManager &) const override;

	};

}