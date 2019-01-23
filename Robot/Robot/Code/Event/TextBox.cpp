#include "TextBox.h"
#include "../Input/InputManager.h"


namespace
{
	const int DRAW_TEXT_SPAN = 5; // �`��

	const String NO_ICON = L"NoIcon"; // �A�C�R����\�����̕\���摜

	const Point TEXT_BOX_DRAW_POS(0, 320);       // �e�L�X�g�{�b�N�X��\��������W
	const Point ICON_DRAW_POS(16,336);           // �A�C�R���̉摜�̕`�悷����W
	const Point TEXT_DRAW_POS(176,336);          // �e�L�X�g��\��������W
}


void Robot::TextBox::set(const String & speakerName, const String & iconName, const String & text)
{
	_isReady        = false;
	_drawTextLength = 0;
	_speakerName    = speakerName;
	_iconName       = iconName;
	_text           = text;
}


void Robot::TextBox::reset()
{
	_isReady        = true;
	_drawTextLength = 0;
	_speakerName    = L"";
	_iconName       = NO_ICON;
	_text           = L"";
}


void Robot::TextBox::update()
{
	static int frameCount = 0;

	if (_drawTextLength >= _text.length)
	{
		if (InputManager::Instance().decision()) { reset(); }
		return;
	}

	if (++frameCount%DRAW_TEXT_SPAN == 0)
	{
		++_drawTextLength;
	}

	if (InputManager::Instance().decision())
	{
		_drawTextLength = _text.length;
	}
}


void Robot::TextBox::draw() const
{
	TextureAsset(L"TextBox").draw(TEXT_BOX_DRAW_POS);

	TextureAsset(_iconName).draw(ICON_DRAW_POS);

	FontAsset(L"15")(_speakerName + L"\n" + _text.substr(0, _drawTextLength)).draw(TEXT_DRAW_POS);
}
