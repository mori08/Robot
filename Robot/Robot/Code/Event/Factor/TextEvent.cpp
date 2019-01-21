#include "TextEvent.h"


namespace
{
	const size_t INFO_SIZE = 3; // �ڍׂ̔z��̃T�C�Y

	const size_t SPEAKER_NAME = 0; // �b����̖��O�̃C���f�b�N�X
	const size_t ICON_NAME    = 1; // �A�C�R���̉摜�̖��O�̃C���f�b�N�X
	const size_t TEXT         = 2; // �\������e�L�X�g�̃C���f�b�N�X
}


bool Robot::TextEvent::load(const Info & info, const EventManager &)
{
	if (info.size() != INFO_SIZE)
	{
		printError(L"�����̃T�C�Y���Ⴂ�܂�");
		printError(L"���o�l : " + ToString(info.size()) + L" , ���Ғl : " + ToString(INFO_SIZE));
		return false;
	}

	_speakerName = info[SPEAKER_NAME];

	_iconName = info[ICON_NAME];
	if (!TextureAsset::IsRegistered(_iconName))
	{
		printError(L"�摜[" + _iconName + L"]�͑��݂��܂���");
		return false;
	}

	_text = info[TEXT];

	return _isSuccess = true;
}


void Robot::TextEvent::perform(EventManager & eventManager) const
{
	eventManager.setTextBox(_speakerName, _iconName, _text);
}


bool Robot::TextEvent::isCompleted(const EventManager & eventManager) const
{
	return eventManager.isReadyTextBox();
}
