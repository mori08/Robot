#include "WaitEvent.h"


namespace
{
	const size_t ARG_SIZE = 1; // コンストラクタで扱う引数のサイズ

	const size_t WAIT_FRAME_COUNT = 0; // 待機フレーム数のインデックス
}


Robot::WaitEvent::WaitEvent(const std::vector<String>& arg)
{
	if (arg.size() != ARG_SIZE)
	{
#ifdef _DEBUG
		Println(L"Error > WaitEventで引数のサイズが誤っています");
#endif // _DEBUG

		_isSuccess = false;
		return;
	}

	Optional<int> opt = FromStringOpt<int>(arg[WAIT_FRAME_COUNT]);

	if (!opt)
	{
#ifdef _DEBUG
		Println(L"Error > WaitEventで数値でない値が指定されました : ", arg[WAIT_FRAME_COUNT]);
#endif // _DEBUG

		_isSuccess = false;
		return;
	}

	_waitFrameCount = *opt;
}


void Robot::WaitEvent::perform(EventManager & eventManager) const
{
	eventManager.resetFrameCount();
}


bool Robot::WaitEvent::isCompleted(const EventManager & eventManager) const
{
	return eventManager.getFrameCount() >= _waitFrameCount;
}
