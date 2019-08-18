#include "EventBase.h"


Robot::EventBase::EventBase()
	: _isSuccess(false)
{
}


void Robot::EventBase::checkAndPerform() const
{
	if (!_isSuccess) { return; }

	perform();
}
