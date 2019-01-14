#include "ActEvent.h"


namespace
{
	const size_t ARG_SIZE = 2; // �R���X�g���N�^�ň��������̃T�C�Y

	const size_t OBJECT_NAME = 0; // �I�u�W�F�N�g�̖��O�̃C���f�b�N�X
	const size_t ACT_NAME    = 1; // ���o�̖��O�̃C���f�b�N�X
}


Robot::ActEvent::ActEvent(const std::vector<String>& arg)
{
	if (arg.size() != ARG_SIZE)
	{
#ifdef _DEBUG
		Println(L"Error > ActEvent�ň����̃T�C�Y������Ă��܂�");
#endif // _DEBUG
		_isSuccess = false;
		return;
	}

	_objectName = arg[OBJECT_NAME];
	_actName    = arg[ACT_NAME];
}


void Robot::ActEvent::perform(EventManager & eventManager) const
{
	auto objOpt = eventManager.getObjectOpt(_objectName);

	if (!objOpt)
	{
#ifdef _DEBUG
		Println(L"Error > ActEvent��Object��������܂���ł����B : ", _objectName);
#endif // _DEBUG
		return;
	}

	(*objOpt)->setAct(_actName);
}


bool Robot::ActEvent::isCompleted(const EventManager & eventManager) const
{
	return eventManager.isWaitingObject(_objectName);
}
