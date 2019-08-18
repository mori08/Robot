#include "ShadowEvent.h"


namespace
{
	const size_t INFO_SIZE = 1; // �ڍׂ̔z��̃T�C�Y

	const size_t SHADOW = 0; // �e�̕t�^�ɂ��ẴC���f�b�N�X
}


bool Robot::ShadowEvent::load(const Info & info)
{
	if (info.size() != INFO_SIZE)
	{
		printError(L"�����̃T�C�Y���Ⴂ�܂�");
		printError(L"���o�l : " + ToString(info.size()) + L" , ���Ғl : " + ToString(INFO_SIZE));
		return false;
	}

	if      (info[SHADOW] == L"TRUE")  { _shadow = true; }
	else if (info[SHADOW] == L"FALSE") { _shadow = false; }
	else
	{
		printError(L"��l�ł͂Ȃ��l���w�肳��܂���");
		printError(L"shadow : " + info[SHADOW]);
		return false;
	}

	return _isSuccess = true;
}


void Robot::ShadowEvent::perform() const
{
	EventManager::Instance().setShadow(_shadow);
}


bool Robot::ShadowEvent::isCompleted() const
{
	return true;
}
