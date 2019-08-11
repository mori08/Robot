#include "ReloadEvent.h"


bool Robot::ReloadEvent::load(const Info & info, const EventManager &)
{
	if (!info.empty())
	{
		printError(L"引数のサイズが違います");
		printError(L"検出値 : " + ToString(info.size()) + L" , 期待値 : " + ToString(0));
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
