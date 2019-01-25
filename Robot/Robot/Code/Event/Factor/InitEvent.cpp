#include "InitEvent.h"


namespace
{
	const size_t INFO_SIZE = 2; // 詳細の配列のサイズ

	const size_t OBJECT_NAME = 0; // オブジェクトの名前のインデックス
	const size_t INIT_NAME = 1;   // 初期化関数の名前のインデックス
}


bool Robot::InitEvent::load(const Info & info, const EventManager & eventManager)
{
	if (info.size() != INFO_SIZE)
	{
		printError(L"引数のサイズが違います");
		printError(L"検出値 : " + ToString(info.size()) + L" , 期待値 : " + ToString(INFO_SIZE));
		return false;
	}

	_objectName = info[OBJECT_NAME];
	if (!eventManager.isExistedObject(_objectName))
	{
		printError(L"オブジェクト[" + _objectName + L"]は存在しません");
		return false;
	}

	_initName = info[INIT_NAME];
	if (!eventManager.isExistedAct(_objectName, _initName))
	{
		printError(L"初期化関数[" + _initName + L"]は存在しません");
		return false;
	}

	return _isSuccess = true;
}


void Robot::InitEvent::perform(EventManager & eventManager) const
{
	auto objOpt = eventManager.getObjectOpt(_objectName);

	(*objOpt)->init(_initName);
}


bool Robot::InitEvent::isCompleted(const EventManager &) const
{
	return true;
}
