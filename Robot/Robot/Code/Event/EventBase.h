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
	protected:

		bool _isSuccess;

	public:

		EventBase();

		/// <summary>
		/// Eventが正しくロードできているか確認し、実行します。
		/// </summary>
		/// <param name="eventManager"> EventManager </param>
		void checkAndPerform(EventManager & eventManager) const;

		/// <summary>
		/// 終了しているか示します。
		/// </summary>
		/// <param name="eventManager"> EventManager </param>
		/// <returns> 終了しているとき true , そうでないとき false </returns>
		virtual bool isCompleted(const EventManager & eventManager) const = 0;

	protected:

		/// <summary>
		/// Eventを実行します。
		/// </summary>
		/// <param name="eventManager"> EventManager </param>
		virtual void perform(EventManager & eventManager) const = 0;

	};
}

