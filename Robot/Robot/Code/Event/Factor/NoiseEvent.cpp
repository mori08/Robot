#include "NoiseEvent.h"


namespace
{
	const size_t INFO_SIZE = 1; // �ڍׂ̔z��̃T�C�Y

	const size_t NOISE = 0; // �m�C�Y�̕t�^�ɂ��ẴC���f�b�N�X
}


bool Robot::NoiseEvent::load(const Info & info)
{
	if (info.size() != INFO_SIZE)
	{
		printError(L"�����̃T�C�Y���Ⴂ�܂�");
		printError(L"���o�l : " + ToString(info.size()) + L" , ���Ғl : " + ToString(INFO_SIZE));
		return false;
	}

	if      (info[NOISE] == L"TRUE")  { _noise = true; }
	else if (info[NOISE] == L"FALSE") { _noise = false; }
	else
	{
		printError(L"��l�ł͂Ȃ��l���w�肳��܂���");
		printError(L"shadow : " + info[NOISE]);
		return false;
	}

	return _isSuccess = true;
}


void Robot::NoiseEvent::perform() const
{
	EventManager::Instance().setNoise(_noise);
}


bool Robot::NoiseEvent::isCompleted() const
{
	return true;
}
