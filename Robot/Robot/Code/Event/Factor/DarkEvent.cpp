#include "DarkEvent.h"
#include "../../MyLibrary.h"


namespace
{
	const size_t INFO_SIZE = 1; // �ڍׂ̔z��̃T�C�Y

	const size_t DARK = 0; // �Ó]�ɂ��ẴC���f�b�N�X
}


bool Robot::DarkEvent::load(const Info & info)
{

	if (info.size() != INFO_SIZE)
	{
		printError(L"�����̃T�C�Y���Ⴂ�܂�");
		printError(L"���o�l : " + ToString(info.size()) + L" , ���Ғl : " + ToString(INFO_SIZE));
		return false;
	}

	if      (info[DARK] == L"TRUE")  { _darkAlpha = 0xFF; }
	else if (info[DARK] == L"FALSE") { _darkAlpha = 0; }
	else
	{
		printError(L"��l�ł͂Ȃ��l���w�肳��܂���");
		printError(L"shadow : " + info[DARK]);
		return false;
	}

	return _isSuccess = true;
}


void Robot::DarkEvent::perform() const
{
	EventManager::Instance().setDarkAlpha(_darkAlpha);
}


bool Robot::DarkEvent::isCompleted() const
{
	return EventManager::Instance().completeChangingDarkAlpha();
}
