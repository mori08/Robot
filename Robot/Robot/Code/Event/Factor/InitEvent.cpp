#include "InitEvent.h"
#include "../../MyLibrary.h"


namespace
{
	const size_t INFO_SIZE = 2; // �ڍׂ̔z��̃T�C�Y

	const size_t OBJECT_NAME = 0; // �I�u�W�F�N�g�̖��O�̃C���f�b�N�X
	const size_t INIT_NAME   = 1; // �������֐��̖��O�̃C���f�b�N�X
}


bool Robot::InitEvent::load(const Info & info)
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
		printError(L"�I�u�W�F�N�g[" + _objectName + L"]�͑��݂��܂���");
		return false;
	}

	_initName = info[INIT_NAME];
	if (!EventManager::Instance().isExistedInit(_objectName, _initName))
	{
		printError(L"�������֐�[" + _initName + L"]�͑��݂��܂���");
		return false;
	}

	return _isSuccess = true;
}


void Robot::InitEvent::perform() const
{
	auto objOpt = EventManager::Instance().getObjectOpt(_objectName);

	(*objOpt)->init(_initName);
}


bool Robot::InitEvent::isCompleted() const
{
	return true;
}
