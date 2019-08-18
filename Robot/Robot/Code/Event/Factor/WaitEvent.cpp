#include "WaitEvent.h"


namespace
{
	const size_t INFO_SIZE = 1; // 詳細の配列のサイズ

	const size_t WAIT_FRAME_COUNT = 0; // 待機フレーム数のインデックス
}


bool Robot::WaitEvent::load(const Info & info)
{
	if (info.size() != INFO_SIZE)
	{
		printError(L"引数のサイズが違います");
		printError(L"検出値 : " + ToString(info.size()) + L" , 期待値 : " + ToString(INFO_SIZE));
		return false;
	}

	Optional<int> opt = FromStringOpt<int>(info[WAIT_FRAME_COUNT]);
	if (!opt)
	{
		printError(L"数値でない値が指定されました");
		printError(L"span : " + info[WAIT_FRAME_COUNT]);
		return false;
	}
	_waitFrameCount = *opt;

	return _isSuccess = true;
}


void Robot::WaitEvent::perform() const
{
	EventManager::Instance().resetFrameCount();
}


bool Robot::WaitEvent::isCompleted() const
{
	return EventManager::Instance().getFrameCount() >= _waitFrameCount;
}
