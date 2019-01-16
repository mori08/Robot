#include "MoveEvent.h"


namespace
{
	const size_t INFO_SIZE = 5; // �ڍׂ̔z��̃T�C�Y

	const size_t NAME = 0; // �I�u�W�F�N�g�̖��O�̃C���f�b�N�X
	const size_t WAIT = 1; // �҂��̃C���f�b�N�X
	const size_t X    = 2; // X���W�̃C���f�b�N�X
	const size_t Y    = 3; // Y���W�̃C���f�b�N�X
	const size_t SPAN = 4; // �ړ��ɂ�����t���[�����̃C���f�b�N�X

	const int RADIX = 10; // 10�i��
}


bool Robot::MoveEvent::load(const Info & info, const EventManager & eventManager)
{
	if (info.size() == INFO_SIZE)
	{
		printError(L"�����̃T�C�Y���Ⴂ�܂�");
		printError(L"���o�l : " + ToString(info.size()) + L" , ���Ғl : " + ToString(INFO_SIZE));
		return false;
	}

	_name = info[NAME];
	if (eventManager.isExistedObject(_name))
	{
		printError(L"�I�u�W�F�N�g[" + _name + L"]�͑��݂��܂���");
		return false;
	}

	if      (info[WAIT] == L"TRUE")  { _wait = true; }
	else if (info[WAIT] == L"FALSE") { _wait = false; }
	else
	{
		printError(L"��l�ł͂Ȃ��l���w�肳��܂���");
		printError(L"wait : " + info[WAIT]);
		return false;
	}

	Optional<int> optX    = FromStringOpt<int>(info[X], 10);
	Optional<int> optY    = FromStringOpt<int>(info[Y], 10);
	Optional<int> optSpan = FromStringOpt<int>(info[SPAN], 10);
	if (!optX || !optY || !optSpan)
	{
		printError(L"���l�ł͂Ȃ��l���w�肳��܂���");
		printError(L"");
		return;
	}
	_goal.x = *optX;
	_goal.y = *optY;
	_spanMoveFrameCount = *optSpan;

	return _isSuccess = true;
}

void Robot::MoveEvent::perform(EventManager & eventManager) const
{
	auto objOpt = eventManager.getObjectOpt(_name);

	if (!objOpt)
	{
#ifdef _DEBUG
		Println(L"Error > MoveEvent��Object��������܂���ł����B : ", _name);
#endif // _DEBUG
		return;
	}

	(*objOpt)->setLinearMove(_goal, _spanMoveFrameCount);
}

bool Robot::MoveEvent::isCompleted(const EventManager & eventManager) const
{
	if (!_wait)
	{
		return true;
	}

	return eventManager.isWaitingObject(_name);
}
