#include "ActEvent.h"


namespace
{
	const size_t INFO_SIZE = 2; // 詳細の配列のサイズ

	const size_t OBJECT_NAME = 0; // オブジェクトの名前のインデックス
	const size_t ACT_NAME    = 1; // 演出の名前のインデックス
}


bool Robot::ActEvent::load(const Info & info, const EventManager & eventManager)
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
		printError(L"オブジェクト["+_objectName + L"]は存在しません");
		return false;
	}

	_actName = info[ACT_NAME];
	if (!eventManager.isExistedAct(_objectName, _actName))
	{
		printError(L"演出[" + _actName + L"]は存在しません");
		return false;
	}

	return _isSuccess = true;
}


void Robot::ActEvent::perform(EventManager & eventManager) const
{
	auto objOpt = eventManager.getObjectOpt(_objectName);

	if (!objOpt)
	{
#ifdef _DEBUG
		Println(L"Error > ActEventでObjectが見つかりませんでした。 : ", _objectName);
#endif // _DEBUG
		return;
	}

	(*objOpt)->setAct(_actName);
}


bool Robot::ActEvent::isCompleted(const EventManager & eventManager) const
{
	return eventManager.isWaitingObject(_objectName);
}
