#include "EventBase.h"


Robot::EventBase::EventBase()
	: _isSuccess(false)
{
}


void Robot::EventBase::checkAndPerform(EventManager & eventManager) const
{
	if (!_isSuccess) { return; }

	perform(eventManager);
}
