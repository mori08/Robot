#include "ReloadEvent.h"
#include "../../MyLibrary.h"


bool Robot::ReloadEvent::load(const Info & info)
{
	if (!info.empty())
	{
		printError(L"�����̃T�C�Y���Ⴂ�܂�");
		printError(L"���o�l : " + ToString(info.size()) + L" , ���Ғl : " + ToString(0));
		return false;
	}

	return _isSuccess = true;
}


void Robot::ReloadEvent::perform() const
{
	EventManager::Instance().reload();
}


bool Robot::ReloadEvent::isCompleted() const
{
	return true;
}
