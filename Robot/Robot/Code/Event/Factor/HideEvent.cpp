#include "HideEvent.h"
#include "../../MyLibrary.h"


namespace
{
	const size_t INFO_SIZE = 2; // 詳細の配列のサイズ

	const size_t NAME = 0; // オブジェクトの名前のインデックス
	const size_t HIDE = 1; // 非表示についてのインデックス
}


bool Robot::HideEvent::load(const Info & info)
{
	if (info.size() != INFO_SIZE)
	{
		printError(L"引数のサイズが違います");
		printError(L"検出値 : " + ToString(info.size()) + L" , 期待値 : " + ToString(INFO_SIZE));
		return false;
	}

	_name = info[NAME];
	if (!EventManager::Instance().isExistedObject(_name))
	{
		printError(L"オブジェクト[" + _name + L"]は存在しません");
		return false;
	}

	if      (info[HIDE] == L"TRUE")  { _hide = true; }
	else if (info[HIDE] == L"FALSE") { _hide = false; }
	else
	{
		printError(L"二値ではない値が指定されました");
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
		Println(L"Error > MoveEventでObjectが見つかりませんでした。 : ", _name);
#endif // _DEBUG
		return;
	}

	(*objOpt)->setHide(_hide);
}


bool Robot::HideEvent::isCompleted() const
{
	return true;
}
