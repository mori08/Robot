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

		using ObjectPtr  = std::shared_ptr<EventObject>;
		using ObjectList = std::map<String, ObjectPtr>;

		using EventPtr      = std::unique_ptr<EventBase>;
		using EventInfo     = std::vector<String>;
		using MakeEventFunc = std::function<EventPtr()>;
		using MakeEventMap  = std::unordered_map<String, MakeEventFunc>;

		using EventQueue = std::queue<EventPtr>;

	private:

		bool         _isSuccess;           // ロードが成功しているか

		ObjectList   _objectList;          // EventOjectのリスト

		EventQueue   _eventQueue;          // EventBaseの派生を取り出すキュー

		MakeEventMap _makeEventMap;        // イベントを生成する関数の連想配列

		String       _backgroundName;      // 背景画像の名前

		int          _frameCount;          // 経過フレーム数

		double       _shakeSize;           // 画面の揺れの大きさ

		int          _shakeFrameCount;     // 画面の揺れについての経過フレーム数

		int          _spanShakeFrameCount; // 画面を揺らす期間

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
		/// CSVデータをイベントに変換します。
		/// </summary>
		/// <param name="eventFileName"> csvファイルの名前 </param>
		/// <returns> 変換に成功したとき true , そうでないとき false </returns> 
		bool translateEventData(const CSVReader & eventFile);

		/// <summary>
		/// １つのイベントをマップに登録します。
		/// </summary>
		/// <param name="name"> イベント名 </param>
		template<typename eventType>
		void setEvent(const String & name)
		{
			_makeEventMap[name] = MakeEventFunc
			(
				[]()
				{
					return std::move(std::make_unique<eventType>());
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

		/// <summary>
		/// エラーメッセージを出力します。
		/// </summary>
		/// <param name="message"> メッセージ </param>
		void printError(const String & message)
		{
#ifdef _DEBUG
			Println(message);
#endif // _DEBUG
		}

	public: // EventSceneで使用する関数

		/// <summary>
		/// イベントを記述したcsvファイルを読み込む
		/// </summary>
		/// <param name="eventFileName"> csvファイルの名前 </param>
		void load(const String & eventFileName);

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

		/// <summary>
		/// オブジェクトが存在するか示します。
		/// </summary>
		/// <param name="name"> オブジェクトの名前 </param>
		/// <returns> 存在するとき true , そうでないとき false </returns>
		bool isExistedObject(const String & name) const
		{
			return _objectList.find(name) != _objectList.end();
		}

		/// <summary>
		/// あるオブジェクトの演出が存在するか示します。
		/// </summary>
		/// <param name=""objectName> オブジェクトの名前 </param>
		/// <param name="actName"> 演出の名前 </param>
		/// <returns> 存在するとき true , そうでないとき false </returns>
		bool isExistedAct(const String & objectName, const String & actName) const
		{
			return isExistedObject(objectName) && _objectList.find(objectName)->second->isExistedAct(actName);
		}

		/// <summary>
		/// オブジェクトのポインタを取得します。
		/// </summary>
		/// <param name="name"> オブジェクトの名前 </param>
		/// <returns> 名前に対応するオブジェクトが存在するときそのポインタ , しないとき none </returns>
		Optional<ObjectPtr> getObjectOpt(const String & name);

		/// <summary>
		/// オブジェクトが待ち状態か示します。
		/// </summary>
		/// <param name="name"> オブジェクトの名前 </param>
		bool isWaitingObject(const String & name) const;

		/// <summary>
		/// 画面の揺れを設定します。
		/// </summary>
		/// <param name="size"> 揺れの大きさ </param>
		/// <param name="span"> 揺らす時間 </param>
		void setShake(double size, int span)
		{
			if (size < 0 || span < 0)
			{
#ifdef _DEBUG
				Println(L"Error > setShake関数で不適切な値が指定されました。");
				Println(L"[size : ", size, L"][span : ", span, L"]");
#endif // _DEBUG
				return;
			}

			_shakeSize           = size;
			_shakeFrameCount     = 0;
			_spanShakeFrameCount = span;
		}

		/// <summary>
		/// 画面の揺れが終了しているか示します。
		/// </summary>
		/// <returns> 終了しているとき true , そうでないとき false </returns>
		bool isCompleteShaking() const
		{
			return _shakeFrameCount > _spanShakeFrameCount;
		}

	};

}