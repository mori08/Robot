#include "HideEvent.h"


namespace
{
	const size_t INFO_SIZE = 2; // �ڍׂ̔z��̃T�C�Y

	const size_t NAME = 0; // �I�u�W�F�N�g�̖��O�̃C���f�b�N�X
	const size_t HIDE = 1; // ��\���ɂ��ẴC���f�b�N�X
}


bool Robot::HideEvent::load(const Info & info)
{
	if (info.size() != INFO_SIZE)
	{
		printError(L"�����̃T�C�Y���Ⴂ�܂�");
		printError(L"���o�l : " + ToString(info.size()) + L" , ���Ғl : " + ToString(INFO_SIZE));
		return false;
	}

	_name = info[NAME];
	if (!EventManager::Instance().isExistedObject(_name))
	{
		printError(L"�I�u�W�F�N�g[" + _name + L"]�͑��݂��܂���");
		return false;
	}

	if      (info[HIDE] == L"TRUE")  { _hide = true; }
	else if (info[HIDE] == L"FALSE") { _hide = false; }
	else
	{
		printError(L"��l�ł͂Ȃ��l���w�肳��܂���");
		printError(L"wait : " + info[HIDE]);
		return false;
	}

	return _isSuccess = true;
}


void Robot::HideEvent::perform() const
{
	auto objOpt = EventManager::Instance().getObjectOpt(_name);

	if (!objOpt)
	{
#ifdef _DEBUG
		Println(L"Error > MoveEvent��Object��������܂���ł����B : ", _name);
#endif // _DEBUG
		return;
	}

	(*objOpt)->setHide(_hide);
}


bool Robot::HideEvent::isCompleted() const
{
	return true;
}
