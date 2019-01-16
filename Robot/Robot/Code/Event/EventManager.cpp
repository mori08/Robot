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
	const int EVENT_NAME_COLUMN = 0;      // CSV�t�@�C�����̃C�x���g�̖��O���L�q�����
	const int EVENT_INFO_COLUMN = 1;      // CSV�t�@�C�����̃C�x���g�̏ڍׂ��ŏ��ɋL�q�����
	const String EVENT_INFO_END = L"#";   // CSV�t�@�C�����ŃC�x���g�̏ڍׂ̍Ō�Ɏg��������
	const String RUN_EVENT_KEY  = L"Run"; // CSV�t�@�C�����œo�^�ς݂̃C�x���g��S�Ď��s���閽��
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
		// �C�x���g�̖��O�̎擾
		String eventName = eventFile.get<String>(loadingRow, EVENT_NAME_COLUMN);

		// ���݃L���[�ɂ���S�C�x���g�����s����
		if (eventName == RUN_EVENT_KEY) 
		{
			runAllEvent();
			continue;
		}

		// �C�x���g�����݂��邩���m�F
		if (_makeEventMap.find(eventName) == _makeEventMap.end())
		{
			Println(L"�C�x���g[" + eventName + L"] �͑��݂��܂���");
			Println(L"[", eventFile.path(), L"] ", loadingRow + 1, L"�s��");
			return false;
		}

		// �C�x���g�̏ڍׂ̍쐬
		EventInfo eventInfo;
		for (int column = EVENT_INFO_COLUMN; ; ++column)
		{
			// �I��������������Ȃ��Ƃ��G���[
			if (column >= eventFile.columns(loadingRow))
			{
				printError(L"�I������[" + EVENT_INFO_END + L"]������܂���");
				printError(L"[" + eventFile.path() + L"] " + ToString(loadingRow + 1) + L"�s��");
				return false;
			}

			// �I�����������������Ƃ����[�v�𔲂���
			if (eventFile.get<String>(loadingRow, column) == EVENT_INFO_END) { break; }

			// �ڍׂɒǉ�����
			eventInfo.emplace_back(eventFile.get<String>(loadingRow, column));
		}

		// �C�x���g�̃|�C���^�𐶐�����
		EventPtr eventPtr = _makeEventMap[eventName]();

		// �C�x���g�̏ڍׂ�ǂݍ��݂܂�
		if (!eventPtr->load(eventInfo, *this))
		{
			printError(L"[" + eventFile.path() + L"] " + ToString(loadingRow + 1) + L"�s��");
			return false;
		}

		// �L���[�ɃC�x���g��ǉ�����
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
	// ���������s���܂�
	resetFrameCount();
	_objectList.clear();
	while (!_eventQueue.empty()) { _eventQueue.pop(); }
	_eventQueue.push(std::make_unique<InitEvent>());

	CSVReader reader(eventFileName);
	if (!reader.isOpened())
	{
		printError(L"Error > Event��ǂݍ��߂܂���ł����B : " + eventFileName);
		return;
	}

	_isSuccess = translateEventData(reader);
}


void Robot::EventManager::update()
{
	++_frameCount;
	++_shakeFrameCount;

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
	Vec2 s = Vec2::Zero; // ��ʂ̗h��

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


