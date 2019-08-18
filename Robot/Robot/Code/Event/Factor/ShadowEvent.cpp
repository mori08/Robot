#include "ShadowEvent.h"
#include "../../MyLibrary.h"


namespace
{
	const size_t INFO_SIZE = 1; // 詳細の配列のサイズ

	const size_t SHADOW = 0; // 影の付与についてのインデックス
}


bool Robot::ShadowEvent::load(const Info & info)
{
	if (info.size() != INFO_SIZE)
	{
		printError(L"引数のサイズが違います");
		printError(L"検出値 : " + ToString(info.size()) + L" , 期待値 : " + ToString(INFO_SIZE));
		return false;
	}

	if      (info[SHADOW] == L"TRUE")  { _shadow = true; }
	else if (info[SHADOW] == L"FALSE") { _shadow = false; }
	else
	{
		printError(L"二値ではない値が指定されました");
		printError(L"shadow : " + info[SHADOW]);
		return false;
	}

	return _isSuccess = true;
}


void Robot::ShadowEvent::perform() const
{
	EventManager::Instance().setShadow(_shadow);
}


bool Robot::ShadowEvent::isCompleted() const
{
	return true;
}
