#include "GenerateEvent.h"

#include "../Object/TestEventObject.h"


Robot::GenerateEvent::FuncMap Robot::GenerateEvent::generateObjMap;


Robot::GenerateEvent::GenerateEvent(const String & type, const String & name, const String & x, const String & y)
	: _type(type)
	, _name(name)
{
	if (generateObjMap.find(_type) == generateObjMap.end()) 
	{
#ifdef _DEBUG
		Println(L"Error > GenrateEvent�œo�^����Ă��Ȃ��I�u�W�F�N�g���w�肳��܂����B");
#endif // _DEBUG

		_isSuccess = false;
		return;
	}

	Optional<int> optX = FromStringOpt<int>(x, 10);
	Optional<int> optY = FromStringOpt<int>(y, 10);

	if (!optX || !optY)
	{
#ifdef _DEBUG
		Println(L"Error > GenrateEvent�Ő��l�łȂ����W���w�肳��܂����B");
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
