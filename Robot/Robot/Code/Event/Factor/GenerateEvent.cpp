#include "GenerateEvent.h"

#include "../Object/TestEventObject.h"
#include "../Object/BoxRobotObject.h"
#include "../Object/HelpRobotObject.h"
#include "../Object/TelevisionObject.h"


namespace
{
	const size_t INFO_SIZE = 4; // 詳細の配列のサイズ

	const size_t TYPE = 0; // オブジェクトの種類のインデックス
	const size_t NAME = 1; // オブジェクトの名前のインデックス
	const size_t X    = 2; // X座標のインデックス
	const size_t Y    = 3; // Y座標のインデックス

	const int RADIX = 10; // 10進数
}


Robot::GenerateEvent::FuncMap Robot::GenerateEvent::generateObjMap;


bool Robot::GenerateEvent::load(const Info & info, const EventManager &)
{
	if (info.size() != INFO_SIZE)
	{
		printError(L"引数のサイズが違います");
		printError(L"検出値 : " + ToString(info.size()) + L" , 期待値 : " + ToString(INFO_SIZE));
		return false;
	}

	_type = info[TYPE];
	_name = info[NAME];
	if (generateObjMap.find(_type) == generateObjMap.end())
	{
		printError(L"オブジェクトの型[" + _type + L"]は存在しません");
		return false;
	}

	Optional<int> optX = FromStringOpt<int>(info[X], RADIX);
	Optional<int> optY = FromStringOpt<int>(info[Y], RADIX);
	if (!optX || !optY)
	{
		printError(L"数値ではない値が指定されました");
		printError(L"x : " + info[X] + L" , y : " + info[Y]);
		return false;
	}
	_pos.x = *optX;
	_pos.y = *optY;

	return _isSuccess = true;
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
	makeGenerateFunc<TestEventObject> (L"TestEventObject");
	makeGenerateFunc<BoxRobotObject>  (L"BoxRobot");
	makeGenerateFunc<HelpRobotObject> (L"HelpRobot");
	makeGenerateFunc<TelevisionObject>(L"Television");

}
