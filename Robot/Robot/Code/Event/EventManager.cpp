#include "EventManager.h"

#include "Factor\InitEvent.h"
#include "Factor\GenerateEvent.h"
#include "Factor\BackgroundEvent.h"
#include "Factor\WaitEvent.h"
#include "Factor\MoveEvent.h"


namespace
{
	const int EVENT_NAME_COLUMN = 0;      // CSV�t�@�C�����̃C�x���g�̖��O���L�q�����
	const int EVENT_INFO_COLUMN = 1;      // CSV�t�@�C�����̃C�x���g�̏ڍׂ��ŏ��ɋL�q�����
	const String EVENT_INFO_END = L".";   // CSV�t�@�C�����ŃC�x���g�̏ڍׂ̍Ō�Ɏg��������
	const String RUN_EVENT_KEY  = L"Run"; // CSV�t�@�C�����œo�^�ς݂̃C�x���g��S�Ď��s���閽��
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

	// �L���[�̒�����ɂ��A�����C�x���g��push���܂�
	while (!_eventQueue.empty()) { _eventQueue.pop(); }
	_eventQueue.push(std::make_unique<InitEvent>());

	CSVReader reader(eventName);

	if (!reader.isOpened())
	{
#ifdef _DEBUG
		Println(L"Error > Event��ǂݍ��߂܂���ł����B");
#endif // _DEBUG

		return;
	}

	int loadingEventId = 0; // ���ݓǂݍ��ݒ��̃C�x���g�̍s�ԍ�

	for (; loadingEventId < reader.rows; ++loadingEventId)
	{
		String eventKey = reader.get<String>(loadingEventId, EVENT_NAME_COLUMN);

		if (eventKey == RUN_EVENT_KEY)
		{
			runAllEvent();
			continue;
		}

		// �����̍쐬
		EventArg eventArg;
		for (int i = EVENT_INFO_COLUMN; ; ++i)
		{
			if (i >= reader.columns(loadingEventId))
			{
#ifdef _DEBUG
				Println(L"Error > Event�ɏI������������܂��� : ", loadingEventId, L"�s��");
#endif // _DEBUG
				break;
			}

			if (reader.get<String>(loadingEventId, i) == EVENT_INFO_END) { break; }

			eventArg.emplace_back(reader.get<String>(loadingEventId, i));
		}

		// �}�b�v����C�x���g��T��
		if (_makeEventMap.find(eventKey) == _makeEventMap.end())
		{
#ifdef _DEBUG
			Println(L"Error > �o�^����Ă��Ȃ��C�x���g�ł� : ", loadingEventId+1, L"�s��");
#endif // _DEBUG

			continue;
		}

		// �L���[�ɃC�x���g��ǉ�����
		_eventQueue.push(_makeEventMap[eventKey](eventArg));
	}
}


void Robot::EventManager::update()
{
	++_frameCount;

	// �L���[�̒��ɃC�x���g��1�����Ȃ�X�L�b�v
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


