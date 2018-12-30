#include "EventObject.h"


const Robot::EventObject::Act Robot::EventObject::noAct(std::make_shared<std::function<void()>>([](){}));


Robot::EventObject::EventObject()
{

}


void Robot::EventObject::setLinearMove(const Point & goal, int spanFrameCount)
{
	if(_moveFrameCount>0)

	_moveRange.first  = _pos;
	_moveRange.second = goal;

	_moveFrameCount     = 0;
	_spanMoveFrameCount = spanFrameCount;
}


void Robot::EventObject::setAct(const String & actName)
{
#ifdef _DEBUG
	if (_actMap.find(actName) == _actMap.end())
	{
		Println(L"Error > setAct�֐��œo�^����Ă��Ȃ����o���Ă΂�܂���", actName);
		return;
	}
#endif // _DEBUG

	_act           = _actMap[actName];
	_isActing      = true;
	_actFrameCount = 0;
}

void Robot::EventObject::update()
{
	(*_act)();

	moveObject();
}

void Robot::EventObject::draw() const
{
	TextureAsset(_textureName).drawAt(_pos);
}


void Robot::EventObject::moveObject()
{
	if (++_moveFrameCount > _spanMoveFrameCount) { return; }

	double rate = 1.0*_moveFrameCount / _spanMoveFrameCount;

	_pos = ((1 - rate)*_moveRange.first + rate*_moveRange.second).asPoint();
}
