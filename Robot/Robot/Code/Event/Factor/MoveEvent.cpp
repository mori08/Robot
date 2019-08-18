#include "MoveEvent.h"


namespace
{
	const size_t INFO_SIZE = 5; // 詳細の配列のサイズ

	const size_t NAME = 0; // オブジェクトの名前のインデックス
	const size_t WAIT = 1; // 待ちのインデックス
	const size_t X    = 2; // X座標のインデックス
	const size_t Y    = 3; // Y座標のインデックス
	const size_t SPAN = 4; // 移動にかかるフレーム数のインデックス

	const int RADIX = 10; // 10進数
}


bool Robot::MoveEvent::load(const Info & info)
{
	if (info.size() != INFO_SIZE)
	{
		printError(L"引数のサイズが違います");
		printError(L"検出値 : " + ToString(info.size()) + L" , 期待値 : " + ToString(INFO_SIZE));
		return false;
	}

	_name = info[NAME];
	if (!EventManager::Instance().isExistedObject(_name))
	{
		printError(L"オブジェクト[" + _name + L"]は存在しません");
		return false;
	}

	if      (info[WAIT] == L"TRUE")  { _wait = true; }
	else if (info[WAIT] == L"FALSE") { _wait = false; }
	else
	{
		printError(L"二値ではない値が指定されました");
		printError(L"wait : " + info[WAIT]);
		return false;
	}

	Optional<int> optX    = FromStringOpt<int>(info[X], 10);
	Optional<int> optY    = FromStringOpt<int>(info[Y], 10);
	Optional<int> optSpan = FromStringOpt<int>(info[SPAN], 10);
	if (!optX || !optY || !optSpan)
	{
		printError(L"数値ではない値が指定されました");
		printError(L"x : " + info[X] + L" , y : " + info[Y] + L" , span : " + info[SPAN]);
		return false;
	}
	_goal.x = *optX;
	_goal.y = *optY;
	_spanMoveFrameCount = *optSpan;

	return _isSuccess = true;
}

void Robot::MoveEvent::perform() const
{
	auto objOpt = EventManager::Instance().getObjectOpt(_name);

	if (!objOpt)
	{
#ifdef _DEBUG
		Println(L"Error > MoveEventでObjectが見つかりませんでした。 : ", _name);
#endif // _DEBUG
		return;
	}

	(*objOpt)->setLinearMove(_goal, _spanMoveFrameCount);
}

bool Robot::MoveEvent::isCompleted() const
{
	if (!_wait)
	{
		return true;
	}

	return EventManager::Instance().isWaitingObject(_name);
}
