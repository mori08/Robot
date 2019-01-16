#pragma once


#include<Siv3D.hpp>


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

	このクラスの派生クラスを作るときは
	EventManagerのsetAllEvent関数に登録する
	*/
	class EventBase
	{
	protected:

		using Info = std::vector<String>;

	protected:

		bool _isSuccess;

	public:

		EventBase();

		/// <summary>
		/// 文字列の配列を受け取り、イベントの詳細を決定します。
		/// </summary>
		/// <param name="info"> イベントの詳細 </param>
		/// <param name="eventManager"> EventManager </param>
		/// <returns> 正しく決定できたとき true , そうでないとき false </returns>
		virtual bool load(const Info & info, const EventManager & eventManager) = 0;

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

		/// <summary>
		/// エラーメッセージを出力します。
		/// </summary>
		/// <param name="message"> エラーの内容 </param>
		/// <remarks> デバッグモードでのみ出力します。 </remarks>
		void printError(const String & message)
		{
#ifdef _DEBUG
			Println(message);
#endif // _DEBUG
		}

	};
}

