#include "EventObject.h"


namespace
{
	/// <summary>
	/// ���l����`�I�ɕύX���܂��B
	/// </summary>
	/// <param name="s"> �n�_ </param>
	/// <param name="t"> �I�_ </param>
	/// <param name="r"> ������ </param>
	int changeLinearly(int s, int t, double r)
	{
		if (s == t) { return s; }

		return static_cast<int>((1 - r)*s + r*t);
	}
}


const Robot::EventObject::ActPtr Robot::EventObject::noAct(std::make_shared<std::function<void()>>([](){}));


Robot::EventObject::EventObject(const Point & pos)
	: _pos(pos)
	, _moveRange({ pos,pos })
	, _moveFrameCount(0)
	, _spanMoveFrameCount(0)
	, _isActing(false)
	, _actFrameCount(0)
	, _act(noAct)
	, _isHidding(false)
{

}


void Robot::EventObject::setLinearMove(const Point & goal, int spanFrameCount)
{
	if (spanFrameCount == 0)
	{
		_pos = _moveRange.first = _moveRange.second = goal;

		_moveFrameCount     = 0;
		_spanMoveFrameCount = 0;
		return;
	}

	_moveRange.first  = _pos;
	_moveRange.second = goal;

	_moveFrameCount     = 0;
	_spanMoveFrameCount = spanFrameCount;
}


void Robot::EventObject::init(const String & initName)
{
#ifdef _DEBUG
	if (!isExistedInit(initName))
	{
		Println(L"Error > setInit�֐��œo�^����Ă��Ȃ��֐����Ă΂�܂��� : ", initName);
		return;
	}
#endif // _DEBUG

	(*_initMap[initName])();
}


void Robot::EventObject::setAct(const String & actName)
{
#ifdef _DEBUG
	if (_actMap.find(actName) == _actMap.end())
	{
		Println(L"Error > setAct�֐��œo�^����Ă��Ȃ����o���Ă΂�܂��� : ", actName);
		return;
	}
#endif // _DEBUG

	_act           = _actMap[actName];
	_isActing      = true;
	_actFrameCount = 0;
}

void Robot::EventObject::update()
{
	++_moveFrameCount;
	++_actFrameCount;

	(*_act)();

	moveObject();
}


void Robot::EventObject::checkHiddingAndDraw(const Vec2 & shakeSize) const
{
	if (_isHidding)return;

	draw(shakeSize);
}


void Robot::EventObject::finishAct()
{
	_act      = noAct;
	_isActing = false;
}


void Robot::EventObject::moveObject()
{
	if (_moveFrameCount > _spanMoveFrameCount) { return; }

	double rate = 1.0*_moveFrameCount / _spanMoveFrameCount;

	_pos.x = changeLinearly(_moveRange.first.x, _moveRange.second.x, rate);
	_pos.y = changeLinearly(_moveRange.first.y, _moveRange.second.y, rate);
}
