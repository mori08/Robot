#include "GenerateEvent.h"

#include "../Object/TestEventObject.h"


namespace
{
	const size_t ARG_SIZE = 4; // コンストラクタで扱う引数のサイズ
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

	_type = arg[0];
	_name = arg[1];

	if (generateObjMap.find(_type) == generateObjMap.end()) 
	{
#ifdef _DEBUG
		Println(L"Error > 登録されていないEventObjectがです。", _type);
#endif // _DEBUG

		_isSuccess = false;
		return;
	}

	Optional<int> optX = FromStringOpt<int>(arg[2], 10);
	Optional<int> optY = FromStringOpt<int>(arg[3], 10);

	if (!optX || !optY)
	{
#ifdef _DEBUG
		Println(L"Error > GenrateEventで数値でない座標が指定されました。");
		Println(L"[x : ", *optX, L"] [y : ", *optY, L"]");
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
