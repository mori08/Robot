#include "WaitEvent.h"


namespace
{
	const size_t INFO_SIZE = 1; // �ڍׂ̔z��̃T�C�Y

	const size_t WAIT_FRAME_COUNT = 0; // �ҋ@�t���[�����̃C���f�b�N�X
}


bool Robot::WaitEvent::load(const Info & info, const EventManager &)
{
	if (info.size() != INFO_SIZE)
	{
		printError(L"�����̃T�C�Y���Ⴂ�܂�");
		printError(L"���o�l : " + ToString(info.size()) + L" , ���Ғl : " + ToString(INFO_SIZE));
		return false;
	}

	Optional<int> opt = FromStringOpt<int>(info[WAIT_FRAME_COUNT]);
	if (!opt)
	{
		printError(L"���l�łȂ��l���w�肳��܂���");
		printError(L"span : " + info[WAIT_FRAME_COUNT]);
		return false;
	}
	_waitFrameCount = *opt;

	return _isSuccess = true;
}


void Robot::WaitEvent::perform(EventManager & eventManager) const
{
	eventManager.resetFrameCount();
}


bool Robot::WaitEvent::isCompleted(const EventManager & eventManager) const
{
	return eventManager.getFrameCount() >= _waitFrameCount;
}
