#include "EventManager.h"

#include "Factor\GenerateEvent.h"


namespace
{
	const int EVENT_NAME_COLUMN = 0;    // CSVファイル中のイベントの名前を記述する列数
	const int EVENT_INFO_COLUMN = 1;    // CSVファイル中のイベントの詳細を最初に記述する列数
	const String EVENT_INFO_END = L"/"; // CSVファイル中でイベントの詳細の最後に使う文字列
}


Robot::EventManager::EventManager()
{

}


void Robot::EventManager::setAllEvent()
{
	setEvent<GenerateEvent>(L"Generate");
}


void Robot::EventManager::load(const String & eventName)
{
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
		// 引数の作成
		EventArg eventArg;
		for (int i = EVENT_INFO_COLUMN; i < reader.columns(loadingEventId) && reader.get<String>(loadingEventId, i) != EVENT_INFO_END; ++i)
		{
			eventArg.emplace_back(reader.get<String>(loadingEventId, i));
		}

		String eventName = reader.get<String>(loadingEventId, EVENT_NAME_COLUMN);

		// マップからイベントを探す
		if (_makeEventMap.find(eventName) == _makeEventMap.end())
		{
			Println(L"Error > 登録されていないイベントです : ", loadingEventId, L"行目");
			continue;
		}

		// キューにイベントを追加する
		_eventQueue.push(_makeEventMap[eventName](eventArg));
	}
}


void Robot::EventManager::update()
{
	if (!_eventQueue.empty() && _eventQueue.front()->isCompleted(*this))
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
	for (const auto & object : _objectList)
	{
		object.second->draw();
	}
}


void Robot::EventManager::generateObject(const String & name, const std::shared_ptr<EventObject>& object)
{
	_objectList[name] = object;
}
