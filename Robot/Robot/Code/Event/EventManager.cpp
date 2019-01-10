#include "EventManager.h"

#include "Factor\GenerateEvent.h"


namespace
{
	const int EVENT_NAME_COLUMN = 0;    // CSV�t�@�C�����̃C�x���g�̖��O���L�q�����
	const int EVENT_INFO_COLUMN = 1;    // CSV�t�@�C�����̃C�x���g�̏ڍׂ��ŏ��ɋL�q�����
	const String EVENT_INFO_END = L"/"; // CSV�t�@�C�����ŃC�x���g�̏ڍׂ̍Ō�Ɏg��������
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
		Println(L"Error > Event��ǂݍ��߂܂���ł����B");
#endif // _DEBUG

		return;
	}

	int loadingEventId = 0; // ���ݓǂݍ��ݒ��̃C�x���g�̍s�ԍ�

	for (; loadingEventId < reader.rows; ++loadingEventId)
	{
		// �����̍쐬
		EventArg eventArg;
		for (int i = EVENT_INFO_COLUMN; i < reader.columns(loadingEventId) && reader.get<String>(loadingEventId, i) != EVENT_INFO_END; ++i)
		{
			eventArg.emplace_back(reader.get<String>(loadingEventId, i));
		}

		String eventName = reader.get<String>(loadingEventId, EVENT_NAME_COLUMN);

		// �}�b�v����C�x���g��T��
		if (_makeEventMap.find(eventName) == _makeEventMap.end())
		{
			Println(L"Error > �o�^����Ă��Ȃ��C�x���g�ł� : ", loadingEventId, L"�s��");
			continue;
		}

		// �L���[�ɃC�x���g��ǉ�����
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
