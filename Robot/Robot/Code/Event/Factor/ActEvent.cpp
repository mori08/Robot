#include "ActEvent.h"
#include "../../MyLibrary.h"


namespace
{
	const size_t INFO_SIZE = 2; // �ڍׂ̔z��̃T�C�Y

	const size_t OBJECT_NAME = 0; // �I�u�W�F�N�g�̖��O�̃C���f�b�N�X
	const size_t ACT_NAME    = 1; // ���o�̖��O�̃C���f�b�N�X
}


bool Robot::ActEvent::load(const Info & info)
{
	if (info.size() != INFO_SIZE)
	{
		printError(L"�����̃T�C�Y���Ⴂ�܂�");
		printError(L"���o�l : " + ToString(info.size()) + L" , ���Ғl : " + ToString(INFO_SIZE));
		return false;
	}

	_objectName = info[OBJECT_NAME];
	if (!EventManager::Instance().isExistedObject(_objectName))
	{
		printError(L"�I�u�W�F�N�g["+_objectName + L"]�͑��݂��܂���");
		return false;
	}

	_actName = info[ACT_NAME];
	if (!EventManager::Instance().isExistedAct(_objectName, _actName))
	{
		printError(L"���o[" + _actName + L"]�͑��݂��܂���");
		return false;
	}

	return _isSuccess = true;
}


void Robot::ActEvent::perform() const
{
	auto objOpt = EventManager::Instance().getObjectOpt(_objectName);

	if (!objOpt)
	{
#ifdef _DEBUG
		Println(L"Error > ActEvent��Object��������܂���ł����B : ", _objectName);
#endif // _DEBUG
		return;
	}

	(*objOpt)->setAct(_actName);
}


bool Robot::ActEvent::isCompleted() const
{
	return EventManager::Instance().isWaitingObject(_objectName);
}
