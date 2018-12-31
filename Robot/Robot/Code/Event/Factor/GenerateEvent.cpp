#include "GenerateEvent.h"


Robot::GenerateEvent::FuncMap Robot::GenerateEvent::generateObjMap;


Robot::GenerateEvent::GenerateEvent(const String & type, const String & name, const String & x, const String & y)
	: _type(type)
	, _name(name)
{
	if (generateObjMap.find(_type) == generateObjMap.end()) 
	{
#ifdef _DEBUG
		Println(L"Error > GenrateEventで登録されていないオブジェクトが指定されました。");
#endif // _DEBUG

		_isSuccess = false;
		return;
	}

	Optional<int> optX = FromStringOpt<int>(x, 10);
	Optional<int> optY = FromStringOpt<int>(y, 10);

	if (!optX || !optY)
	{
#ifdef _DEBUG
		Println(L"Error > GenrateEventで数値でない座標が指定されました。");
#endif // _DEBUG

		_isSuccess = false;
		return;
	}

	_pos.x = *optX;
	_pos.y = *optY;
}


void Robot::GenerateEvent::perform(EventManager & eventManager) const
{
	eventManager.generateObject(_name, generateObjMap[_type]());
}


bool Robot::GenerateEvent::isCompleted(const EventManager &) const
{
	return true;
}


void Robot::GenerateEvent::setObjectMap()
{

}
