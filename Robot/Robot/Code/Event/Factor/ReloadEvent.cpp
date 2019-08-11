#include "ReloadEvent.h"


bool Robot::ReloadEvent::load(const Info & info, const EventManager &)
{
	if (!info.empty())
	{
		printError(L"�����̃T�C�Y���Ⴂ�܂�");
		printError(L"���o�l : " + ToString(info.size()) + L" , ���Ғl : " + ToString(0));
		return false;
	}

	return _isSuccess = true;
}


void Robot::ReloadEvent::perform(EventManager & eventManager) const
{
	eventManager.reload();
}


bool Robot::ReloadEvent::isCompleted(const EventManager &) const
{
	return true;
}
