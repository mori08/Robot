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
	const double COLOR_CHANGE_RATE = 0.90; // 色の変更の割合
	const double CURSOR_MOVE_RATE  = 0.8;  // カーソルが動くときの割合

	const double MIN_COLOR_DIFFERENCE = 0.01; // 色の誤差の最小値
}


const ColorF Robot::MenuWindowBase::NON_SHOWED_COLOR  (ColorF(Palette::MyWhite), 0.0);
const ColorF Robot::MenuWindowBase::SHOWED_COLOR      (ColorF(Palette::MyWhite), 0.1);
const ColorF Robot::MenuWindowBase::NON_SELECTED_COLOR(ColorF(Palette::MyWhite), 0.4);
const ColorF Robot::MenuWindowBase::SELECTED_COLOR    (ColorF(Palette::MyWhite), 1.0);


Robot::MenuWindowBase::MenuWindowBase()
{
	_state = std::unique_ptr<ClosedState>();
	_closedProcessing = nullptr;
	_white = NON_SHOWED_COLOR;
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


void Robot::MenuWindowBase::updateSelectedWindowButton()
{
	_selectedButtonKey = InputManager::Instance().getSelectedButton().getKey();

	_cursor.pos = CURSOR_MOVE_RATE*_cursor.pos + (1 - CURSOR_MOVE_RATE)*InputManager::Instance().getSelectedButton().getRegion().pos;

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
	_cursor.movedBy(offset).draw(_white);
	
	for (const auto button : _buttonPtrList)
	{
		ColorF color = _selectedButtonKey == button->getKey() ? Palette::MyBlack : _white;
		FontAsset(L"15")(L" ", _buttonNameMap.find(button->getKey())->second).draw(button->getPoint() + offset, color);
	}
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
