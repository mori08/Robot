#include "GenerateEvent.h"


Robot::GenerateEvent::GenerateEvent(const String & type, const String & name, const String & x, const String & y)
	: _type(type)
	, _name(name)
{
	if (objectMap.find(_type) == objectMap.end()) 
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

}


void Robot::GenerateEvent::setObjectMap()
{

}
