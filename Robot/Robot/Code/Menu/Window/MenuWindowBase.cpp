#include "MenuWindowBase.h"
#include "../../MyColor.h"
#include "../../Input/InputManager.h"
#include "../Window/State/ClosedState.h"
#include "../Window/State/OpenedState.h"
#include "../Window/State/SelectedState.h"
#include "../Window/State/OpeningState.h"
#include "../Window/State/ClosingState.h"


namespace
{
	const double COLOR_CHANGE_RATE = 0.85; // 色の変更の割合
	const double CURSOR_MOVE_RATE  = 0.8;  // カーソルが動くときの割合

	const double MIN_COLOR_DIFFERENCE = 0.01; // 色の誤差の最小値
}


const ColorF Robot::MenuWindowBase::NON_SHOWED_COLOR  (ColorF(Palette::MyWhite), 0.0);
const ColorF Robot::MenuWindowBase::SHOWED_COLOR      (ColorF(Palette::MyWhite), 0.1);
const ColorF Robot::MenuWindowBase::NON_SELECTED_COLOR(ColorF(Palette::MyWhite), 0.4);
const ColorF Robot::MenuWindowBase::SELECTED_COLOR    (ColorF(Palette::MyWhite), 1.0);

const double Robot::MenuWindowBase::BOARD_ALPHA = 0.5;


Robot::MenuWindowBase::MenuWindowBase()
	: _defaultButton(L"", Rect())
{
	_state = std::unique_ptr<ClosedState>();
	_closedProcessing = nullptr;
	_white = NON_SHOWED_COLOR;
	_boardColor = ColorF(Palette::MyBlack, 0);
}


void Robot::MenuWindowBase::load()
{
	resetButton();
	makeButton();
	if (!_buttonNameMap.count(_selectedButtonKey))
	{
		_selectedButtonKey = _defaultButton.first;
		_cursor.second     = _defaultButton.second;
	}
	_cursor.first = _cursor.second;
}


void Robot::MenuWindowBase::update()
{
	if (_state == nullptr) { 
		return; 
	}
	
	_state->update(*this);
}


void Robot::MenuWindowBase::draw() const
{
	if (_state == nullptr) { return; }
	_state->draw(*this);
}


void Robot::MenuWindowBase::open()
{
	_selectedButtonKey = _defaultButton.first;
	_cursor            = { _defaultButton.second,_defaultButton.second };

	_state = std::make_unique<OpeningState>(_openOffset);
}


void Robot::MenuWindowBase::select()
{
	_state = std::make_unique<SelectedState>();
}


void Robot::MenuWindowBase::nonSelect()
{
	_state = std::make_unique<OpenedState>();
}


void Robot::MenuWindowBase::close()
{
	_state = std::make_unique<ClosingState>(_openOffset);
}


void Robot::MenuWindowBase::setColor(const ColorF & color)
{
	changeColor(_white, color);
}


void Robot::MenuWindowBase::moveCursol()
{
	_cursor.first.pos = CURSOR_MOVE_RATE*_cursor.first.pos + (1 - CURSOR_MOVE_RATE)*_cursor.second.pos;
}


void Robot::MenuWindowBase::setBoardAlpha(double alpha)
{
	changeColor(_boardColor, ColorF(Palette::MyBlack, alpha));
}


void Robot::MenuWindowBase::updateSelectedWindowButton()
{
	_selectedButtonKey = InputManager::Instance().getSelectedButton().getKey();
	_cursor.second.pos = InputManager::Instance().getSelectedButton().getRegion().pos;

	moveCursol();

	changeColor(_white, SELECTED_COLOR);

	if (InputManager::Instance().option() && _closedProcessing != nullptr)
	{
		(*_closedProcessing)();
		return;
	}

	Optional<String> selectButtonKey = InputManager::Instance().selectButton();

	if (selectButtonKey)
	{
		if (processingExists(*selectButtonKey))
		{
			(*_processingMap[*selectButtonKey])();
		}
	}
	else if (InputManager::Instance().decision() && _closedProcessing != nullptr)
	{
		(*_closedProcessing)();
	}
}


void Robot::MenuWindowBase::drawButtonAndLight(const Vec2 & offset) const
{
	for (const auto & button : _buttonPtrList)
	{
		button->getRegion().draw(_boardColor);
	}

	_cursor.first.movedBy(offset).draw(_white);
	
	for (const auto & button : _buttonPtrList)
	{
		ColorF color = _selectedButtonKey == button->getKey() ? Palette::MyBlack : Palette::MyWhite;
		color.a = _white.a;
		FontAsset(L"15")(L" ", _buttonNameMap.find(button->getKey())->second).draw(button->getPoint() + offset, color);
	}
}


void Robot::MenuWindowBase::resetButton()
{
	_buttonPtrList.clear();
	_buttonNameMap.clear();
	_processingMap.clear();
}


void Robot::MenuWindowBase::registerButton(const String & buttonKey, const Rect & region, ProcessingPtr processing)
{
	_buttonPtrList.emplace_back(std::make_shared<Button>(buttonKey, region));

	_processingMap[buttonKey] = std::move(processing);

	_buttonNameMap[buttonKey] = buttonKey;
}


void Robot::MenuWindowBase::changeColor(ColorF & color, const ColorF & goalColor)
{
	color.a = COLOR_CHANGE_RATE*color.a + (1 - COLOR_CHANGE_RATE)*goalColor.a;
	if (Abs(color.a - goalColor.a) < MIN_COLOR_DIFFERENCE)
	{
		color.a = goalColor.a;
	}
}
