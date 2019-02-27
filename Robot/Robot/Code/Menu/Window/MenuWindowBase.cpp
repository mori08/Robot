#include "MenuWindowBase.h"
#include "../../Input/InputManager.h"


namespace
{
	const double COLOR_CHANGE_RATE = 0.95; // �F�̕ύX�̊���

	const ColorF WHITE(0.9); // ��
	const ColorF GRAY(0.3);  // �D
	const double MIN_COLOR_DIFFERENCE = 0.05; // �F�̌덷�̍ŏ��l

	const double BLUR_RADIUS = 5.0;   // �e�̂ڂ�����
	const double SHADOW_SPREAD = 3.0; // �e�̍L�����
}


void Robot::MenuWindowBase::update()
{
	_selectedButtonKey = InputManager::Instance().getSelectedButton().getKey();
	ClearPrint();
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

		Println(button->getKey(), L" : ", _colorMap[button->getKey()]);
	}

	Optional<String> selectButtonKey = InputManager::Instance().selectButton();

	if (selectButtonKey && processingExists(*selectButtonKey))
	{		
		(*_processingMap[*selectButtonKey])();
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
	if (color.r - goalColor.r < MIN_COLOR_DIFFERENCE)
	{
		color = goalColor;
	}
}
