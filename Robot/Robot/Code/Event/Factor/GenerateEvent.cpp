#include "GenerateEvent.h"

#include "../Object/TestEventObject.h"


namespace
{
	const size_t ARG_SIZE = 4; // コンストラクタで扱う引数のサイズ

	const size_t TYPE = 0; // オブジェクトの種類のインデックス
	const size_t NAME = 1; // オブジェクトの名前のインデックス
	const size_t X    = 2; // X座標のインデックス
	const size_t Y    = 3; // Y座標のインデックス
}


Robot::GenerateEvent::FuncMap Robot::GenerateEvent::generateObjMap;


Robot::GenerateEvent::GenerateEvent(const std::vector<String> & arg)
{
	if (arg.size() != ARG_SIZE)
	{
#ifdef _DEBUG
		Println(L"Error > GenrateEventで引数のサイズが誤っています");
#endif // _DEBUG

		_isSuccess = false;
	}

	_type = arg[TYPE];
	_name = arg[NAME];

	if (generateObjMap.find(_type) == generateObjMap.end()) 
	{
#ifdef _DEBUG
		Println(L"Error > 登録されていないEventObjectがです。", _type);
#endif // _DEBUG

		_isSuccess = false;
		return;
	}

	Optional<int> optX = FromStringOpt<int>(arg[X], 10);
	Optional<int> optY = FromStringOpt<int>(arg[Y], 10);

	if (!optX || !optY)
	{
#ifdef _DEBUG
		Println(L"Error > GenrateEventで数値でない座標が指定されました。");
		Println(L"[x : ", arg[X], L"] [y : ", arg[Y], L"]");
#endif // _DEBUG

		_isSuccess = false;
		return;
	}

	_pos.x = *optX;
	_pos.y = *optY;
}


void Robot::GenerateEvent::perform(EventManager & eventManager) const
{
	eventManager.generateObject(_name, generateObjMap[_type](_pos));
}


bool Robot::GenerateEvent::isCompleted(const EventManager &) const
{
	return true;
}


void Robot::GenerateEvent::setObjectMap()
{
	makeGenerateFunc<TestEventObject>(L"TestEventObject");
}
