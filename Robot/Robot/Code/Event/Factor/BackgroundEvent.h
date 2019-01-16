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

	private:

		bool load(const Info & info, const EventManager & eventManager)override;

		void perform(EventManager & eventManager) const override;

		bool isCompleted(const EventManager &) const override;

	};

}