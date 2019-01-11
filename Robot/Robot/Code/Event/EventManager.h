#pragma once

#include<Siv3D.hpp>

#include<queue>

#include"Object/EventObject.h"

#include"Factor/EventBase.h"

namespace Robot
{
	/*
	EventManagerクラス
	CSVファイルからEventを読み込み
	EventObjectの管理
	背景や効果，演出の設定
	*/
	class EventManager
	{
	private:

		using ObjectList = std::map<String, std::shared_ptr<EventObject>>;
		using EventQueue = std::queue<std::unique_ptr<EventBase>>;

		using EventPtr      = std::unique_ptr<EventBase>;
		using EventArg      = std::vector<String>;
		using MakeEventFunc = std::function<EventPtr(const EventArg &)>;
		using MakeEventMap  = std::unordered_map<String, MakeEventFunc>;

	private:

		ObjectList   _objectList;     // EventOjectのリスト

		EventQueue   _eventQueue;     // EventBaseの派生を取り出すキュー

		MakeEventMap _makeEventMap;   // イベントを生成する関数の連想配列

		String       _backgroundName; // 背景画像の名前

		int          _frameCount;     // 経過フレーム数

	private:

		EventManager();

		EventManager(const EventManager&)            = default;
		EventManager& operator=(const EventManager&) = default;
		EventManager(EventManager&&)                 = default;
		EventManager& operator=(EventManager&&)      = default;

	public:

		/// <summary>
		/// シングルトンとして管理しているEventManagerのインスタンスを取得します。
		/// </summary>
		/// <returns> インスタンス </returns>
		static EventManager & Instance()
		{
			static EventManager eventManager;
			return eventManager;
		}

		/// <summary>
		/// 全てのイベントをマップに登録します。
		/// </summary>
		void setAllEvent();

	private:

		/// <summary>
		/// １つのイベントをマップに登録します。
		/// </summary>
		/// <param name="name"> イベント名 </param>
		template<typename eventType>
		void setEvent(const String & name)
		{
			_makeEventMap[name] = MakeEventFunc
			(
				[](const EventArg & eventArg)
				{
					return std::move(std::make_unique<eventType>(eventArg));
				}
			);
		}

		/// <summary>
		/// Eventのファイルを読み込み中に_eventQueue内の全Eventを実行します。
		/// </summary>
		/// <remarks>
		/// 初期化用に行います。
		/// isCompleted関数での判定待ちは行いません
		/// </remarks>
		void runAllEvent();

	public: // EventSceneで使用する関数

		/// <summary>
		/// イベントを記述したcsvファイルを読み込む
		/// </summary>
		/// <param name="eventName"> csvファイルの名前 </param>
		void load(const String & eventName);

		/// <summary>
		/// 更新
		/// </summary>
		void update();

		/// <summary>
		/// 描画
		/// </summary>
		void draw() const;

	public: // EventBaseの派生クラスで使用する関数

		/// <summary>
		/// EventObjectを追加します。
		/// </summary>
		/// <param name="name"> 名前 </param>
		/// <param name="object"> オブジェクト </param>
		void generateObject(const String & name ,const std::shared_ptr<EventObject> & object)
		{
			_objectList[name] = object;
		}

		/// <summary>
		/// 背景を設定します。
		/// </summary>
		/// <param name="name"> 背景画像の名前 </param>
		void setBackground(const String & name)
		{
			_backgroundName = name;
		}

		/// <summary>
		/// 経過フレーム数を取得します。
		/// </summary>
		int getFrameCount() const
		{
			return _frameCount;
		}

		/// <summary>
		/// 経過フレーム数を0にします。
		/// </summary>
		void resetFrameCount()
		{
			_frameCount = 0;
		}

	};

}