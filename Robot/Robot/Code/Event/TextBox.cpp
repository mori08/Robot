#include "TextBox.h"
#include "../Input/InputManager.h"


namespace
{
	const int DRAW_TEXT_SPAN = 5; // 描画

	const Point TEXT_BOX_DRAW_POS(0, 320); // テキストボックスを表示する座標
}


void Robot::TextBox::set(const String & text, const String & speakerName, const String & iconName)
{
	_drawTextLength = 0;
	_text           = text;
	_speakerName    = speakerName;
	_iconName       = iconName;
}


void Robot::TextBox::reset()
{
	_drawTextLength = 0;
	_text           = L"";
	_speakerName    = L"";
	_iconName       = L"";
}


void Robot::TextBox::update()
{
	static int frameCount = 0;

	if (++frameCount%DRAW_TEXT_SPAN == 0 && _drawTextLength < _text.length)
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
}
