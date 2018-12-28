#pragma once

namespace Robot
{
	/*
	EventBaseクラスの実装ではEventManagerクラスの参照のみ使用する
	EventManagerクラスの実装はEventManager.hとEventManager.cppで行う
	*/
	class EventManager;

	/*
	EventBaseクラス
	csvファイルからイベントを読み込んだとき
	その1行分がこのクラスに対応する
	イベントの種類ごとにこのクラスの派生クラスを作成する
	*/
	class EventBase
	{
	public:

		virtual void perform(EventManager & eventManager)const = 0;

	};
}

