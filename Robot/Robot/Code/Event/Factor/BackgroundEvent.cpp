#include "BackgroundEvent.h"


namespace
{
	const size_t ARG_SIZE = 1; // コンストラクタで扱う引数のサイズ

	const size_t NAME = 0; // 背景画像の名前のインデックス
}


Robot::BackgroundEvent::BackgroundEvent(const std::vector<String> & arg)
{
	if (arg.size() != ARG_SIZE)
	{
#ifdef _DEBUG
		Println(L"Error > BackgroundEventで引数のサイズが誤っています");
		Println(arg);
#endif // _DEBUG

		_isSuccess = false;
	}
	
	_name = arg[NAME];
}


void Robot::BackgroundEvent::perform(EventManager & eventManager) const
{
	eventManager.setBackground(_name);
}


bool Robot::BackgroundEvent::isCompleted(const EventManager &) const
{
	return true;
}
