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
	const int EVENT_NAME_COLUMN = 0;           // CSVファイル中のイベントの名前を記述する列数
	const int EVENT_INFO_COLUMN = 1;           // CSVファイル中のイベントの詳細を最初に記述する列数
	const String EVENT_INFO_END = L"#";        // CSVファイル中でイベントの詳細の最後に使う文字列
	const String RUN_EVENT_KEY  = L"Run";      // CSVファイル中で登録済みのイベントを全て実行する命令
	const String FUNC_EVENT_KEY = L"Function"; // CSVファイル中で別CSVファイルのイベントを読み込む命令
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


bool Robot::EventManager::translateEventData(const CSVReader & eventFile)
{
	for (int loadingRow = 0; loadingRow < eventFile.rows; ++loadingRow)
	{
		// イベントの名前の取得
		String eventName = eventFile.get<String>(loadingRow, EVENT_NAME_COLUMN);

		// 現在キューにある全イベントを実行する
		if (eventName == RUN_EVENT_KEY) 
		{
			runAllEvent();
			continue;
		}
		
		// 別CSVファイルを読み込む
		if (eventName == FUNC_EVENT_KEY)
		{
			String funcFileName = eventFile.get<String>(loadingRow, EVENT_INFO_COLUMN);
			CSVReader reader(L"Asset/Data/Event/Function/" + funcFileName + L".csv");
			if (!reader.isOpened())
			{
				printError(L"イベント関数ファイル[" + reader.path() + L"] は存在しません");
				printError(L"[" + eventFile.path() + L"] " + ToString(loadingRow + 1) + L"行目");
			}
			if (!translateEventData(reader))
			{
				return false;
			}
			continue;
		}

		// イベントが存在するかを確認
		if (_makeEventMap.find(eventName) == _makeEventMap.end())
		{
			printError(L"イベント[" + eventName + L"] は存在しません");
			printError(L"[" + eventFile.path() + L"] " + ToString(loadingRow + 1) + L"行目");
			return false;
		}

		// イベントの詳細の作成
		EventInfo eventInfo;
		for (int column = EVENT_INFO_COLUMN; ; ++column)
		{
			// 終了文字が見つからないときエラー
			if (column >= eventFile.columns(loadingRow))
			{
				printError(L"終了文字[" + EVENT_INFO_END + L"]がありません");
				printError(L"[" + eventFile.path() + L"] " + ToString(loadingRow + 1) + L"行目");
				return false;
			}

			// 終了文字が見つかったときループを抜ける
			if (eventFile.get<String>(loadingRow, column) == EVENT_INFO_END) { break; }

			// 詳細に追加する
			eventInfo.emplace_back(eventFile.get<String>(loadingRow, column));
		}

		// イベントのポインタを生成する
		EventPtr eventPtr = _makeEventMap[eventName]();

		// イベントの詳細を読み込みます
		if (!eventPtr->load(eventInfo, *this))
		{
			printError(L"[" + eventFile.path() + L"] " + ToString(loadingRow + 1) + L"行目");
			return false;
		}

		// キューにイベントを追加する
		_eventQueue.push(std::move(eventPtr));
	}

	return true;
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
	// 初期化を行います
	_isSuccess = false;
	resetFrameCount();
	_objectList.clear();
	while (!_eventQueue.empty()) { _eventQueue.pop(); }
	_eventQueue.push(std::make_unique<InitEvent>());

	CSVReader reader(eventFileName);
	if (!reader.isOpened())
	{
		printError(L"Error > Eventを読み込めませんでした。 : " + eventFileName);
		return;
	}

	_isSuccess = translateEventData(reader);
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


