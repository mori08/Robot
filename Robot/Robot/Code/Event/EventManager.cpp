#include "EventManager.h"

#include "Factor\InitEvent.h"
#include "Factor\GenerateEvent.h"
#include "Factor\BackgroundEvent.h"
#include "Factor\WaitEvent.h"
#include "Factor\MoveEvent.h"
#include "Factor\ActEvent.h"
#include "Factor\ShakeEvent.h"


namespace
{
	const int EVENT_NAME_COLUMN = 0;      // CSVファイル中のイベントの名前を記述する列数
	const int EVENT_INFO_COLUMN = 1;      // CSVファイル中のイベントの詳細を最初に記述する列数
	const String EVENT_INFO_END = L"#";   // CSVファイル中でイベントの詳細の最後に使う文字列
	const String RUN_EVENT_KEY  = L"Run"; // CSVファイル中で登録済みのイベントを全て実行する命令
}


Robot::EventManager::EventManager()
	: _frameCount(0)
	, _shakeSize(0)
	, _shakeFrameCount(0)
	, _spanShakeFrameCount(0)
{

}


void Robot::EventManager::setAllEvent()
{
	setEvent<GenerateEvent>  (L"Generate");
	setEvent<BackgroundEvent>(L"Background");
	setEvent<WaitEvent>      (L"Wait");
	setEvent<MoveEvent>      (L"Move");
	setEvent<ActEvent>       (L"Act");
	setEvent<ShakeEvent>     (L"Shake");
}


void Robot::EventManager::translateEventData(const String & eventFileName)
{

}


void Robot::EventManager::runAllEvent()
{
	while (!_eventQueue.empty())
	{
		_eventQueue.front()->checkAndPerform(*this);
		_eventQueue.pop();
	}

	_eventQueue.push(std::make_unique<InitEvent>());
}


void Robot::EventManager::load(const String & eventFileName)
{
	resetFrameCount();

	_objectList.clear();

	// キューの中を空にし、初期イベントをpushします
	while (!_eventQueue.empty()) { _eventQueue.pop(); }
	_eventQueue.push(std::make_unique<InitEvent>());

	CSVReader reader(eventFileName);

	if (!reader.isOpened())
	{
#ifdef _DEBUG
		Println(L"Error > Eventを読み込めませんでした。 : ", eventFileName);
#endif // _DEBUG
		return;
	}

	int loadingEventId = 0; // 現在読み込み中のイベントの行番号

	for (; loadingEventId < reader.rows; ++loadingEventId)
	{
		String eventKey = reader.get<String>(loadingEventId, EVENT_NAME_COLUMN);

		if (eventKey == RUN_EVENT_KEY)
		{
			runAllEvent();
			continue;
		}

		// マップからイベントを探す
		if (_makeEventMap.find(eventKey) == _makeEventMap.end())
		{
#ifdef _DEBUG
			Println(L"イベント[" + eventKey + L"] は存在しません");
			Println(L"[", eventFileName, L"] ", loadingEventId + 1, L"行目");
#endif // _DEBUG
			continue;
		}

		EventInfo eventInfo; // イベントの詳細をまとめた配列
		for (int i = EVENT_INFO_COLUMN; ; ++i)
		{
			if (i >= reader.columns(loadingEventId))
			{
#ifdef _DEBUG
				Println(L"終了文字[", EVENT_INFO_END, L"]がありません");
				Println(L"[", eventFileName, L"] ", loadingEventId + 1, L"行目");
#endif // _DEBUG
				break;
			}

			if (reader.get<String>(loadingEventId, i) == EVENT_INFO_END) { break; }

			eventInfo.emplace_back(reader.get<String>(loadingEventId, i));
		}

		EventPtr eventPtr = _makeEventMap[eventKey]();

		if (!eventPtr->load(eventInfo, *this))
		{
#ifdef _DEBUG
			Println(L"[", eventFileName, L"] ", loadingEventId + 1, L"行目");
#endif // _DEBUG
			continue;
		}

		// キューにイベントを追加する
		_eventQueue.push(std::move(eventPtr));
	}
}


void Robot::EventManager::update()
{
	++_frameCount;
	++_shakeFrameCount;

	// キューの中にイベントが1つだけならスキップ
	if (_eventQueue.size() > 1 && _eventQueue.front()->isCompleted(*this))
	{
		_eventQueue.pop();
		_eventQueue.front()->checkAndPerform(*this);
	}

	for (auto & object : _objectList)
	{
		object.second->update();
	}
}


void Robot::EventManager::draw() const
{
	Vec2 s = Vec2::Zero; // 画面の揺れ

	if (_shakeFrameCount < _spanShakeFrameCount)
	{
		s.x = Random(-_shakeSize, _shakeSize);
		s.y = Random(-_shakeSize, _shakeSize);
	}

	TextureAsset(_backgroundName).draw(s);

	for (const auto & object : _objectList)
	{
		object.second->draw(s);
	}
}


Optional<Robot::EventManager::ObjectPtr> Robot::EventManager::getObjectOpt(const String & name)
{
	if (_objectList.find(name) == _objectList.end())
	{
		return none;
	}
	
	return _objectList[name];
}


bool Robot::EventManager::isWaitingObject(const String & name) const
{
	if (_objectList.find(name) == _objectList.end())
	{
		return true;
	}

	return _objectList.find(name)->second->completeMoveAndAct();
}


