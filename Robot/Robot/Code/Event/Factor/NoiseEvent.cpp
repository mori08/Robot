#include "NoiseEvent.h"


namespace
{
	const size_t INFO_SIZE = 1; // 詳細の配列のサイズ

	const size_t NOISE = 0; // ノイズの付与についてのインデックス
}


bool Robot::NoiseEvent::load(const Info & info)
{
	if (info.size() != INFO_SIZE)
	{
		printError(L"引数のサイズが違います");
		printError(L"検出値 : " + ToString(info.size()) + L" , 期待値 : " + ToString(INFO_SIZE));
		return false;
	}

	if      (info[NOISE] == L"TRUE")  { _noise = true; }
	else if (info[NOISE] == L"FALSE") { _noise = false; }
	else
	{
		printError(L"二値ではない値が指定されました");
		printError(L"shadow : " + info[NOISE]);
		return false;
	}

	return _isSuccess = true;
}


void Robot::NoiseEvent::perform() const
{
	EventManager::Instance().setNoise(_noise);
}


bool Robot::NoiseEvent::isCompleted() const
{
	return true;
}
