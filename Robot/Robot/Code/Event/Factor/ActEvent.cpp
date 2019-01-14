#include "ActEvent.h"


namespace
{
	const size_t ARG_SIZE = 2; // コンストラクタで扱う引数のサイズ

	const size_t OBJECT_NAME = 0; // オブジェクトの名前のインデックス
	const size_t ACT_NAME    = 1; // 演出の名前のインデックス
}


Robot::ActEvent::ActEvent(const std::vector<String>& arg)
{
	if (arg.size() != ARG_SIZE)
	{
#ifdef _DEBUG
		Println(L"Error > ActEventで引数のサイズが誤っています");
#endif // _DEBUG
		_isSuccess = false;
		return;
	}

	_objectName = arg[OBJECT_NAME];
	_actName    = arg[ACT_NAME];
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
