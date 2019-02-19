#include "MenuWindowBase.h"
#include "../../Input/InputManager.h"


namespace
{
	const double COLOR_CHANGE_RATE = 0.95; // F‚Ì•ÏX‚ÌŠ„‡

	const ColorF WHITE(0.9); // ”’
	const ColorF GRAY(0.3);  // ŠD

	const double BLUR_RADIUS = 5.0;   // ‰e‚Ì‚Ú‚©‚µ•û
	const double SHADOW_SPREAD = 3.0; // ‰e‚ÌL‚ª‚è•û
}


void Robot::MenuWindowBase::update()
{
	_selectedButtonKey = InputManager::Instance().getSelectedButton().getKey();

	for (const auto & button : _buttonPtrList)
	{
		if (button->getKey() == _selectedButtonKey)
		{
			_colorMap[button->getKey()] = COLOR_CHANGE_RATE*_colorMap[button->getKey()] + (1 - COLOR_CHANGE_RATE)*WHITE;
		}
		else
		{
			_colorMap[button->getKey()] = COLOR_CHANGE_RATE*_colorMap[button->getKey()] + (1 - COLOR_CHANGE_RATE)*GRAY;
		}
	}

	Optional<String> selectButtonKey = InputManager::Instance().selectButton();

	if (selectButtonKey && processingExists(*selectButtonKey))
	{		
		(*_processingMap[*selectButtonKey])();
	}
}


void Robot::MenuWindowBase::setClickedProcessing(const String & buttonKey, ProcessingPtr processing)
{
#ifdef _DEBUG
	if (!keyExistsAtButtonList(buttonKey))
	{
		Println(L"setClickedProcessingŠÖ”‚ÅŽw’è‚³‚ê‚½ƒL[‚ªŒ©‚Â‚©‚è‚Ü‚¹‚ñ‚Å‚µ‚½");
		Println(L"buttonKey : ", buttonKey);
	}
#endif // _DEBUG

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
