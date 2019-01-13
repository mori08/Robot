#include "MoveEvent.h"


namespace
{
	const size_t ARG_SIZE = 5;

	const size_t NAME = 0; // オブジェクトの名前のインデックス
	const size_t WAIT = 1; // 待ちのインデックス
	const size_t X    = 2; // X座標のインデックス
	const size_t Y    = 3; // Y座標のインデックス
	const size_t SPAN = 4; // 移動にかかるフレーム数のインデックス
}


Robot::MoveEvent::MoveEvent(const std::vector<String>& arg)
{
	if (arg.size() != ARG_SIZE)
	{
#ifdef _DEBUG
		Println(L"Error > MoveEventで引数のサイズが誤っています");
#endif // _DEBUG

		_isSuccess = false;

		return;
	}

	_name = arg[NAME];

	if (arg[WAIT] == L"TRUE")       { _wait = true; }
	else if (arg[WAIT] == L"FALSE") { _wait = false; }
	else
	{
#ifdef _DEBUG
		Println(L"Error > MoveEventでboolでない値が指定されました : ", arg[WAIT]);
#endif // _DEBUG
		_isSuccess = false;
		return;
	}
	
	Optional<int> optX    = FromStringOpt<int>(arg[X]   , 10);
	Optional<int> optY    = FromStringOpt<int>(arg[Y]   , 10);
	Optional<int> optSpan = FromStringOpt<int>(arg[SPAN], 10);

	if (!optX || !optY || !optSpan)
	{
#ifdef _DEBUG
		Println(L"Error > GenrateEventで数値でない座標が指定されました。");
		Println(L"[x : ", arg[X], L"] [y : ", arg[Y], L"]");
#endif // _DEBUG
		_isSuccess = false;
		return;
	}

	_goal.x             = *optX;
	_goal.y             = *optY;
	_spanMoveFrameCount = *optSpan;
}


void Robot::MoveEvent::perform(EventManager & eventManager) const
{
	auto objOpt = eventManager.getObjectOpt(_name);

	if (!objOpt)
	{
#ifdef _DEBUG
		Println(L"Error > EventObejctでObjectが見つかりませんでした。 : ", _name);
#endif // _DEBUG
		return;
	}

	(*objOpt)->setLinearMove(_goal, _spanMoveFrameCount);
}

bool Robot::MoveEvent::isCompleted(const EventManager & eventManager) const
{
	if (!_wait)
	{
		return true;
	}

	return eventManager.isWaitingObject(_name);
}
