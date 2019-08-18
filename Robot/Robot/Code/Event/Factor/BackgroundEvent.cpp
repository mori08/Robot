#include "BackgroundEvent.h"


namespace
{
	const size_t INFO_SIZE = 1; // 詳細の配列のサイズ

	const size_t NAME = 0; // 背景画像の名前のインデックス
}


bool Robot::BackgroundEvent::load(const Info & info)
{
	if (info.size() != INFO_SIZE)
	{
		printError(L"引数のサイズが違います");
		printError(L"検出値 : " + ToString(info.size()) + L" , 期待値 : " + ToString(INFO_SIZE));
		return false;
	}

	_name = info[NAME];
	if (!TextureAsset::IsRegistered(_name))
	{
		printError(L"画像[" + _name + L"]は存在しません");
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
