#include "EventObject.h"


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
		Println(L"Error > setActŠÖ”‚Å“o˜^‚³‚ê‚Ä‚¢‚È‚¢‰‰o‚ªŒÄ‚Î‚ê‚Ü‚µ‚½", actName);
		return;
	}
#endif // _DEBUG

	_act           = _actMap[actName];
	_isActing      = true;
	_actFrameCount = 0;
}

void Robot::EventObject::update()
{
	_act->operator();

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
