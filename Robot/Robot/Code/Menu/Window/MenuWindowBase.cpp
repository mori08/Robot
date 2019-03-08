#include "MenuWindowBase.h"
#include "../../Input/InputManager.h"
#include "../Window/State/ClosedState.h"
#include "../Window/State/OpenedState.h"
#include "../Window/State/SelectedState.h"
#include "../Window/State/OpeningState.h"
#include "../Window/State/ClosingState.h"


namespace
{
	const double COLOR_CHANGE_RATE = 0.95; // êFÇÃïœçXÇÃäÑçá

	const ColorF WHITE(0.9); // îí
	const ColorF GRAY(0.3);  // äD
	const double MIN_COLOR_DIFFERENCE = 0.01; // êFÇÃåÎç∑ÇÃç≈è¨íl

	const double BLUR_RADIUS = 5.0;   // âeÇÃÇ⁄Ç©Çµï˚
	const double SHADOW_SPREAD = 3.0; // âeÇÃçLÇ™ÇËï˚
}


const ColorF Robot::MenuWindowBase::NON_SHOWED_COLOR  (ColorF(Palette::MyWhite), 0);
const ColorF Robot::MenuWindowBase::NON_SELECTED_COLOR(ColorF(Palette::MyWhite), 0.3);
const ColorF Robot::MenuWindowBase::SELECTED_COLOR    (ColorF(Palette::MyWhite), 1);


Robot::MenuWindowBase::MenuWindowBase()
{
	_state = std::unique_ptr<ClosedState>();
	_closedProcessing = nullptr;
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


void Robot::MenuWindowBase::setClickedProcessing(const String & buttonKey, ProcessingPtr processing)
{
	if (!keyExistsAtButtonList(buttonKey))
	{
		return;
	}

	_processingMap[buttonKey] = std::move(processing);
}


void Robot::MenuWindowBase::setColor(const Color color, size_t num)
{
	num = Min(num, _buttonPtrList.size());
	for (size_t i = 0; i < num; ++i)
	{
		changeColor(_colorMap[_buttonPtrList[i]->getKey()], color);
	}
}


void Robot::MenuWindowBase::updateSelectedWindowButton()
{
	_selectedButtonKey = InputManager::Instance().getSelectedButton().getKey();
	
	for (const auto & button : _buttonPtrList)
	{
		if (button->getKey() == _selectedButtonKey)
		{
			_colorMap[button->getKey()] = Palette::MyWhite;
		}
		else
		{
			changeColor(_colorMap[button->getKey()], NON_SELECTED_COLOR);
		}
	}

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
	for (const auto button : _buttonPtrList)
	{
		button->getRegion().drawShadow(offset, BLUR_RADIUS, SHADOW_SPREAD, _colorMap.find(button->getKey())->second);
		TextureAsset(button->getKey()).draw(button->getRegion().tl + offset);
	}
}


bool Robot::MenuWindowBase::keyExistsAtButtonList(const String & buttonKey) const
{
	for (const auto & button : _buttonPtrList)
	{
		if (button->getKey() == buttonKey) { return true; }
	}
	return false;
}


void Robot::MenuWindowBase::registerButton(const String & buttonKey, const Rect & region)
{
	_buttonPtrList.emplace_back(std::make_shared<Button>(buttonKey, region));

	_colorMap[buttonKey] = ColorF(Palette::MyWhite).setAlpha(0);
}


void Robot::MenuWindowBase::changeColor(ColorF & color, const ColorF & goalColor)
{
	color.a = COLOR_CHANGE_RATE*color.a + (1 - COLOR_CHANGE_RATE)*goalColor.a;
	if (Abs(color.a - goalColor.a) < MIN_COLOR_DIFFERENCE)
	{
		color.a = goalColor.a;
	}
}
