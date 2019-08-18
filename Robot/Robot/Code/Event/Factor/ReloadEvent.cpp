#include "ReloadEvent.h"
#include "../../MyLibrary.h"


bool Robot::ReloadEvent::load(const Info & info)
{
	if (!info.empty())
	{
		printError(L"引数のサイズが違います");
		printError(L"検出値 : " + ToString(info.size()) + L" , 期待値 : " + ToString(0));
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
