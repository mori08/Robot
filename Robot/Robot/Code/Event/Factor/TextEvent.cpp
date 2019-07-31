#include "TextEvent.h"


namespace
{
	const size_t INFO_SIZE = 4; // 詳細の配列のサイズ

	const size_t SPEAKER_NAME = 0; // 話し手の名前のインデックス
	const size_t ICON_NAME    = 1; // アイコンの画像の名前のインデックス
	const size_t TEXT_SPEED   = 2; // テキストを表示する速さ
	const size_t TEXT         = 3; // 表示するテキストのインデックス
}


bool Robot::TextEvent::load(const Info & info, const EventManager &)
{
	if (info.size() != INFO_SIZE)
	{
		printError(L"引数のサイズが違います");
		printError(L"検出値 : " + ToString(info.size()) + L" , 期待値 : " + ToString(INFO_SIZE));
		return false;
	}

	_speakerName = info[SPEAKER_NAME];

	_iconName = info[ICON_NAME];
	if (!TextureAsset::IsRegistered(_iconName))
	{
		printError(L"画像[" + _iconName + L"]は存在しません");
		return false;
	}

	Optional<int> optSpeed = FromStringOpt<int>(info[TEXT_SPEED], 10);
	if (!optSpeed)
	{
		printError(L"数値ではない値が指定されました");
		printError(L"textSpeed : " + info[TEXT_SPEED]);
		return false;
	}
	_textSpeed = *optSpeed;

	_text = info[TEXT];

	return _isSuccess = true;
}


void Robot::TextEvent::perform(EventManager & eventManager) const
{
	eventManager.setTextBox(_speakerName, _iconName, _text, _textSpeed);
}


bool Robot::TextEvent::isCompleted(const EventManager & eventManager) const
{
	return eventManager.isReadyTextBox();
}
