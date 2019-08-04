#include "DarkEvent.h"


namespace
{
	const size_t INFO_SIZE = 1; // 詳細の配列のサイズ

	const size_t DARK = 0; // 暗転についてのインデックス
}


bool Robot::DarkEvent::load(const Info & info, const EventManager &)
{

	if (info.size() != INFO_SIZE)
	{
		printError(L"引数のサイズが違います");
		printError(L"検出値 : " + ToString(info.size()) + L" , 期待値 : " + ToString(INFO_SIZE));
		return false;
	}

	if      (info[DARK] == L"TRUE")  { _darkAlpha = 0xFF; }
	else if (info[DARK] == L"FALSE") { _darkAlpha = 0; }
	else
	{
		printError(L"二値ではない値が指定されました");
		printError(L"shadow : " + info[DARK]);
		return false;
	}

	return _isSuccess = true;
}


void Robot::DarkEvent::perform(EventManager & eventManager) const
{
	eventManager.setDarkAlpha(_darkAlpha);
}


bool Robot::DarkEvent::isCompleted(const EventManager & eventManager) const
{
	return eventManager.completeChangingDarkAlpha();
}
