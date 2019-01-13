#include "EventManager.h"

#include "Factor\InitEvent.h"
#include "Factor\GenerateEvent.h"
#include "Factor\BackgroundEvent.h"
#include "Factor\WaitEvent.h"
#include "Factor\MoveEvent.h"


namespace
{
	const int EVENT_NAME_COLUMN = 0;      // CSVファイル中のイベントの名前を記述する列数
	const int EVENT_INFO_COLUMN = 1;      // CSVファイル中のイベントの詳細を最初に記述する列数
	const String EVENT_INFO_END = L".";   // CSVファイル中でイベントの詳細の最後に使う文字列
	const String RUN_EVENT_KEY  = L"Run"; // CSVファイル中で登録済みのイベントを全て実行する命令
}


Robot::EventManager::EventManager()
{

}


void Robot::EventManager::setAllEvent()
{
	setEvent<GenerateEvent>  (L"Generate");
	setEvent<BackgroundEvent>(L"Background");
	setEvent<WaitEvent>      (L"Wait");
	setEvent<MoveEvent>      (L"Move");
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


void Robot::EventManager::load(const String & eventName)
{
	resetFrameCount();

	// キューの中を空にし、初期イベントをpushします
	while (!_eventQueue.empty()) { _eventQueue.pop(); }
	_eventQueue.push(std::make_unique<InitEvent>());

	CSVReader reader(eventName);

	if (!reader.isOpened())
	{
#ifdef _DEBUG
		Println(L"Error > Eventを読み込めませんでした。");
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

		// 引数の作成
		EventArg eventArg;
		for (int i = EVENT_INFO_COLUMN; ; ++i)
		{
			if (i >= reader.columns(loadingEventId))
			{
#ifdef _DEBUG
				Println(L"Error > Eventに終了文字がありません : ", loadingEventId, L"行目");
#endif // _DEBUG
				break;
			}

			if (reader.get<String>(loadingEventId, i) == EVENT_INFO_END) { break; }

			eventArg.emplace_back(reader.get<String>(loadingEventId, i));
		}

		// マップからイベントを探す
		if (_makeEventMap.find(eventKey) == _makeEventMap.end())
		{
#ifdef _DEBUG
			Println(L"Error > 登録されていないイベントです : ", loadingEventId+1, L"行目");
#endif // _DEBUG

			continue;
		}

		// キューにイベントを追加する
		_eventQueue.push(_makeEventMap[eventKey](eventArg));
	}
}


void Robot::EventManager::update()
{
	++_frameCount;

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
	TextureAsset(_backgroundName).draw();

	for (const auto & object : _objectList)
	{
		object.second->draw();
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


