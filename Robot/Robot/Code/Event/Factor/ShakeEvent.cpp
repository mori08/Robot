#include "ShakeEvent.h"


namespace
{
	const size_t ARG_SIZE = 2; // コンストラクタで扱う引数のサイズ

	const size_t SHAKE_SIZE = 0; // 画面の揺れの大きさのインデックス
	const size_t SHAKE_SPAN = 1; // 画面の揺れの長さのインデックス
}


Robot::ShakeEvent::ShakeEvent(const std::vector<String>& arg)
{
	if (arg.size() != ARG_SIZE)
	{
#ifdef _DEBUG
		Println(L"Error > ShakeEventで引数のサイズが誤っています");
#endif // _DEBUG
		_isSuccess = false;
		return;
	}

	Optional<double> optSize = FromStringOpt<double>(arg[SHAKE_SIZE], 10);
	Optional<int>    optSpan = FromStringOpt<int>   (arg[SHAKE_SPAN], 10);

	if (!optSize || !optSpan)
	{
#ifdef _DEBUG
		Println(L"Error > ShakeEventで数値でない座標が指定されました。");
		Println(L"[shake : ", arg[SHAKE_SIZE], L"] [span : ", arg[SHAKE_SPAN], L"]");
#endif // _DEBUG
		_isSuccess = false;
		return;
	}

	_size = *optSize;
	_span = *optSpan;
}


void Robot::ShakeEvent::perform(EventManager & eventManager) const
{
	eventManager.setShake(_size, _span);
}


bool Robot::ShakeEvent::isCompleted(const EventManager & eventManager) const
{
	return eventManager.isCompleteShaking();
}
