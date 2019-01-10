#include "BackgroundEvent.h"


namespace
{
	const size_t ARG_SIZE = 1; // �R���X�g���N�^�ň��������̃T�C�Y
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
	}
	
	_name = arg[0];
}


void Robot::BackgroundEvent::perform(EventManager & eventManager) const
{
	eventManager.setBackground(_name);
}


bool Robot::BackgroundEvent::isCompleted(const EventManager &) const
{
	return true;
}
