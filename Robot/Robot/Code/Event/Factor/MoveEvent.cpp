#include "MoveEvent.h"


namespace
{
	const size_t ARG_SIZE = 5; // �R���X�g���N�^�ň��������̃T�C�Y

	const size_t NAME = 0; // �I�u�W�F�N�g�̖��O�̃C���f�b�N�X
	const size_t WAIT = 1; // �҂��̃C���f�b�N�X
	const size_t X    = 2; // X���W�̃C���f�b�N�X
	const size_t Y    = 3; // Y���W�̃C���f�b�N�X
	const size_t SPAN = 4; // �ړ��ɂ�����t���[�����̃C���f�b�N�X
}


Robot::MoveEvent::MoveEvent(const std::vector<String>& arg)
{
	if (arg.size() != ARG_SIZE)
	{
#ifdef _DEBUG
		Println(L"Error > MoveEvent�ň����̃T�C�Y������Ă��܂�");
#endif // _DEBUG

		_isSuccess = false;

		return;
	}

	_name = arg[NAME];

	if (arg[WAIT] == L"TRUE")       { _wait = true; }
	else if (arg[WAIT] == L"FALSE") { _wait = false; }
	else
	{
#ifdef _DEBUG
		Println(L"Error > MoveEvent��bool�łȂ��l���w�肳��܂��� : ", arg[WAIT]);
#endif // _DEBUG
		_isSuccess = false;
		return;
	}
	
	Optional<int> optX    = FromStringOpt<int>(arg[X]   , 10);
	Optional<int> optY    = FromStringOpt<int>(arg[Y]   , 10);
	Optional<int> optSpan = FromStringOpt<int>(arg[SPAN], 10);

	if (!optX || !optY || !optSpan)
	{
#ifdef _DEBUG
		Println(L"Error > GenrateEvent�Ő��l�łȂ����W���w�肳��܂����B");
		Println(L"[x : ", arg[X], L"] [y : ", arg[Y], L"]");
#endif // _DEBUG
		_isSuccess = false;
		return;
	}

	_goal.x             = *optX;
	_goal.y             = *optY;
	_spanMoveFrameCount = *optSpan;
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
