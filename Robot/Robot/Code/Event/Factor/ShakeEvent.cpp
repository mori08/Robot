#include "ShakeEvent.h"


namespace
{
	const size_t INFO_SIZE = 2; // 詳細の配列のサイズ

	const size_t SHAKE_SIZE = 0; // 画面の揺れの大きさのインデックス
	const size_t SHAKE_SPAN = 1; // 画面の揺れの長さのインデックス

	const int RADIX = 10;
}


bool Robot::ShakeEvent::load(const Info & info)
{
	if (info.size() != INFO_SIZE)
	{
		printError(L"引数のサイズが違います");
		printError(L"検出値 : " + ToString(info.size()) + L" , 期待値 : " + ToString(INFO_SIZE));
		return false;
	}

	Optional<double> optSize = FromStringOpt<double>(info[SHAKE_SIZE], RADIX);
	Optional<int>    optSpan = FromStringOpt<int>   (info[SHAKE_SPAN], RADIX);
	if (!optSize || !optSpan)
	{
		Println(L"数値でない座標が指定されました。");
		Println(L"shake : ", info[SHAKE_SIZE], L" , span : ", info[SHAKE_SPAN]);
		return false;
	}
	_size = *optSize;
	_span = *optSpan;

	return _isSuccess = true;
}

void Robot::ShakeEvent::perform() const
{
	EventManager::Instance().setShake(_size, _span);
}


bool Robot::ShakeEvent::isCompleted() const
{
	return EventManager::Instance().isCompleteShaking();
}
