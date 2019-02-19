#include "MenuWindowBase.h"


void Robot::MenuWindowBase::setClickedProcessing(const String & buttonKey, ProcessingPtr processing)
{
#ifdef _DEBUG
	if (!keyExistsAtButtonList(buttonKey))
	{
		Println(L"setClickedProcessing�֐��Ŏw�肳�ꂽ�L�[��������܂���ł���");
		Println(L"buttonKey : ", buttonKey);
	}
#endif // _DEBUG

	_processingMap[buttonKey] = std::move(processing);
}


bool Robot::MenuWindowBase::keyExistsAtButtonList(const String & buttonKey) const
{
	for (const auto & button : _buttonPtrList)
	{
		if (button->getKey() == buttonKey) { return true; }
	}
	return false;
}
