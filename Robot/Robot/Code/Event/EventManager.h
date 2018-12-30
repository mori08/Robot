#pragma once

#include<Siv3D.hpp>

#include<queue>

#include"EventObject.h"

#include"EventBase.h"

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

		using ObjectList = std::map<String, EventObject>;

		using EventQueue = std::queue<std::shared_ptr<EventBase>>;

	private:

		ObjectList _objectList; // EventOjectのリスト

		EventQueue _eventQueue; // EventBaseの派生を取り出すキュー

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

	public: // EventSceneで使用する関数

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
		void generateObject(const String & name ,const std::shared_ptr<EventObject> & object);

	};

}