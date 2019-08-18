#include "BackgroundEvent.h"
#include "../../MyLibrary.h"


namespace
{
	const size_t INFO_SIZE = 1; // �ڍׂ̔z��̃T�C�Y

	const size_t NAME = 0; // �w�i�摜�̖��O�̃C���f�b�N�X
}


bool Robot::BackgroundEvent::load(const Info & info)
{
	if (info.size() != INFO_SIZE)
	{
		printError(L"�����̃T�C�Y���Ⴂ�܂�");
		printError(L"���o�l : " + ToString(info.size()) + L" , ���Ғl : " + ToString(INFO_SIZE));
		return false;
	}

	_name = info[NAME];
	if (!TextureAsset::IsRegistered(_name))
	{
		printError(L"�摜[" + _name + L"]�͑��݂��܂���");
		return false;
	}

	return _isSuccess = true;
}


void Robot::BackgroundEvent::perform() const
{
	EventManager::Instance().setBackground(_name);
}


bool Robot::BackgroundEvent::isCompleted() const
{
	return true;
}
