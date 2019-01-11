#include "WaitEvent.h"


namespace
{
	const size_t ARG_SIZE = 1; // �R���X�g���N�^�ň��������̃T�C�Y

	const size_t WAIT_FRAME_COUNT = 0; // �ҋ@�t���[�����̃C���f�b�N�X
}


Robot::WaitEvent::WaitEvent(const std::vector<String>& arg)
{
	if (arg.size() != ARG_SIZE)
	{
#ifdef _DEBUG
		Println(L"Error > WaitEvent�ň����̃T�C�Y������Ă��܂�");
#endif // _DEBUG

		_isSuccess = false;
	}

	Optional<int> opt = FromStringOpt<int>(arg[WAIT_FRAME_COUNT]);

	if (!opt)
	{
#ifdef _DEBUG
		Println(L"Error > WaitEvent�Ő��l�łȂ��l���w�肳��܂��� : ", arg[WAIT_FRAME_COUNT]);
#endif // _DEBUG

		_isSuccess = false;
		return;
	}

	_waitFrameCount = *opt;
}


void Robot::WaitEvent::perform(EventManager & eventManager) const
{
	eventManager.resetFrameCount();
}


bool Robot::WaitEvent::isCompleted(const EventManager & eventManager) const
{
	return eventManager.getFrameCount() >= _waitFrameCount;
}
