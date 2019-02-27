#include "MenuWindowBase.h"
#include "../../Input/InputManager.h"


namespace
{
	const double COLOR_CHANGE_RATE = 0.95; // F‚Ì•ÏX‚ÌŠ„‡

	const ColorF WHITE(0.9); // ”’
	const ColorF GRAY(0.3);  // ŠD
	const double MIN_COLOR_DIFFERENCE = 0.01; // F‚ÌŒë·‚ÌÅ¬’l

	const double BLUR_RADIUS = 5.0;   // ‰e‚Ì‚Ú‚©‚µ•û
	const double SHADOW_SPREAD = 3.0; // ‰e‚ÌL‚ª‚è•û
}


const ColorF Robot::MenuWindowBase::NON_SHOWED_COLOR  (Palette::MyWhite, 0);
const ColorF Robot::MenuWindowBase::NON_SELECTED_COLOR(Palette::MyWhite, 0.3);
const ColorF Robot::MenuWindowBase::NON_SELECTED_COLOR(Palette::MyWhite, 1);

void Robot::MenuWindowBase::update()
{
	_selectedButtonKey = InputManager::Instance().getSelectedButton().getKey();

	for (const auto & button : _buttonPtrList)
	{
		if (button->getKey() == _selectedButtonKey)
		{
			changeColor(_colorMap[button->getKey()], WHITE);
		}
		else
		{
			changeColor(_colorMap[button->getKey()], GRAY);
		}
	}

	Optional<String> selectButtonKey = InputManager::Instance().selectButton();

	if (selectButtonKey && processingExists(*selectButtonKey))
	{		
		(*_processingMap[*selectButtonKey])();
	}
}


void Robot::MenuWindowBase::updateNonSelectedWindow()
{
	for (const auto & button : _buttonPtrList)
	{
		changeColor(_colorMap[button->getKey()], GRAY);
	}
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


void Robot::MenuWindowBase::drawButtonAndLight() const
{
	for (const auto button : _buttonPtrList)
	{
		button->getRegion().drawShadow(Vec2::Zero, BLUR_RADIUS, SHADOW_SPREAD, _colorMap.find(button->getKey())->second);
		TextureAsset(button->getKey()).draw(button->getRegion().tl);
	}
}


void Robot::MenuWindowBase::drawLight() const
{
	for (const auto button : _buttonPtrList)
	{
		button->getRegion().drawShadow(Vec2::Zero, BLUR_RADIUS, SHADOW_SPREAD, _colorMap.find(button->getKey())->second);
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

	_colorMap[buttonKey] = ColorF(Palette::MyBlack);
}


void Robot::MenuWindowBase::changeColor(ColorF & color, const ColorF & goalColor)
{
	color = COLOR_CHANGE_RATE*color + (1 - COLOR_CHANGE_RATE)*goalColor;
	if (Abs(color.a - goalColor.a) < MIN_COLOR_DIFFERENCE)
	{
		color = goalColor;
	}
}
