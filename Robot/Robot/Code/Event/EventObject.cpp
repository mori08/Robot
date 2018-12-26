#include "EventObject.h"


void Robot::EventObject::setLinearMove(const Point & goal, int spanFrameCount)
{
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
