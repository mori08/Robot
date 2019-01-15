#include "ShakeEvent.h"


namespace
{
	const size_t ARG_SIZE = 2; // �R���X�g���N�^�ň��������̃T�C�Y

	const size_t SHAKE_SIZE = 0; // ��ʂ̗h��̑傫���̃C���f�b�N�X
	const size_t SHAKE_SPAN = 1; // ��ʂ̗h��̒����̃C���f�b�N�X
}


Robot::ShakeEvent::ShakeEvent(const std::vector<String>& arg)
{
	if (arg.size() != ARG_SIZE)
	{
#ifdef _DEBUG
		Println(L"Error > ShakeEvent�ň����̃T�C�Y������Ă��܂�");
#endif // _DEBUG
		_isSuccess = false;
		return;
	}

	Optional<double> optSize = FromStringOpt<double>(arg[SHAKE_SIZE], 10);
	Optional<int>    optSpan = FromStringOpt<int>   (arg[SHAKE_SPAN], 10);

	if (!optSize || !optSpan)
	{
#ifdef _DEBUG
		Println(L"Error > ShakeEvent�Ő��l�łȂ����W���w�肳��܂����B");
		Println(L"[shake : ", arg[SHAKE_SIZE], L"] [span : ", arg[SHAKE_SPAN], L"]");
#endif // _DEBUG
		_isSuccess = false;
		return;
	}

	_size = *optSize;
	_span = *optSpan;
}


void Robot::ShakeEvent::perform(EventManager & eventManager) const
{
	eventManager.setShake(_size, _span);
}


bool Robot::ShakeEvent::isCompleted(const EventManager & eventManager) const
{
	return eventManager.isCompleteShaking();
}
