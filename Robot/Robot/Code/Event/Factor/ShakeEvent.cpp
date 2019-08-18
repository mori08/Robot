#include "ShakeEvent.h"


namespace
{
	const size_t INFO_SIZE = 2; // �ڍׂ̔z��̃T�C�Y

	const size_t SHAKE_SIZE = 0; // ��ʂ̗h��̑傫���̃C���f�b�N�X
	const size_t SHAKE_SPAN = 1; // ��ʂ̗h��̒����̃C���f�b�N�X

	const int RADIX = 10;
}


bool Robot::ShakeEvent::load(const Info & info)
{
	if (info.size() != INFO_SIZE)
	{
		printError(L"�����̃T�C�Y���Ⴂ�܂�");
		printError(L"���o�l : " + ToString(info.size()) + L" , ���Ғl : " + ToString(INFO_SIZE));
		return false;
	}

	Optional<double> optSize = FromStringOpt<double>(info[SHAKE_SIZE], RADIX);
	Optional<int>    optSpan = FromStringOpt<int>   (info[SHAKE_SPAN], RADIX);
	if (!optSize || !optSpan)
	{
		Println(L"���l�łȂ����W���w�肳��܂����B");
		Println(L"shake : ", info[SHAKE_SIZE], L" , span : ", info[SHAKE_SPAN]);
		return false;
	}
	_size = *optSize;
	_span = *optSpan;

	return _isSuccess = true;
}

void Robot::ShakeEvent::perform() const
{
	EventManager::Instance().setShake(_size, _span);
}


bool Robot::ShakeEvent::isCompleted() const
{
	return EventManager::Instance().isCompleteShaking();
}
