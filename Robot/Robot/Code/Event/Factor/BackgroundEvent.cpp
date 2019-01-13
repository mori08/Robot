#include "BackgroundEvent.h"


namespace
{
	const size_t ARG_SIZE = 1; // �R���X�g���N�^�ň��������̃T�C�Y

	const size_t NAME = 0; // �w�i�摜�̖��O�̃C���f�b�N�X
}


Robot::BackgroundEvent::BackgroundEvent(const std::vector<String> & arg)
{
	if (arg.size() != ARG_SIZE)
	{
#ifdef _DEBUG
		Println(L"Error > BackgroundEvent�ň����̃T�C�Y������Ă��܂�");
		Println(arg);
#endif // _DEBUG

		_isSuccess = false;
		return;
	}
	
	_name = arg[NAME];
}


void Robot::BackgroundEvent::perform(EventManager & eventManager) const
{
	eventManager.setBackground(_name);
}


bool Robot::BackgroundEvent::isCompleted(const EventManager &) const
{
	return true;
}
