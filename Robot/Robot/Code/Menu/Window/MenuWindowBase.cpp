#include "MenuWindowBase.h"
#include "../../Input/InputManager.h"
#include "../Window/State/ClosedState.h"
#include "../Window/State/OpenedState.h"
#include "../Window/State/SelectedState.h"
#include "../Window/State/OpeningState.h"


namespace
{
	const double COLOR_CHANGE_RATE = 0.95; // 色の変更の割合

	const ColorF WHITE(0.9); // 白
	const ColorF GRAY(0.3);  // 灰
	const double MIN_COLOR_DIFFERENCE = 0.01; // 色の誤差の最小値

	const double BLUR_RADIUS = 5.0;   // 影のぼかし方
	const double SHADOW_SPREAD = 3.0; // 影の広がり方
}


const ColorF Robot::MenuWindowBase::NON_SHOWED_COLOR  (ColorF(Palette::MyWhite), 0);
const ColorF Robot::MenuWindowBase::NON_SELECTED_COLOR(ColorF(Palette::MyWhite), 0.3);
const ColorF Robot::MenuWindowBase::SELECTED_COLOR    (ColorF(Palette::MyWhite), 1);


Robot::MenuWindowBase::MenuWindowBase()
{
	_state = std::unique_ptr<ClosedState>();
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
	_state = std::make_unique<OpeningState>(numOfButton(), _openOffset);
}


void Robot::MenuWindowBase::nonSelect()
{
	_state = std::make_unique<OpenedState>();
}


void Robot::MenuWindowBase::close()
{
	_state = std::make_unique<ClosedState>();
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

	Optional<String> selectButtonKey = InputManager::Instance().selectButton();

	if (selectButtonKey && processingExists(*selectButtonKey))
	{
		(*_processingMap[*selectButtonKey])();
	}
}


void Robot::MenuWindowBase::drawButtonAndLight(const std::vector<Vec2> & offsetList, const std::vector<double> & alphaList) const
{
	size_t i = 0;
	for (const auto button : _buttonPtrList)
	{
		Vec2   offset = (i < offsetList.size()) ? offsetList[i] : Vec2::Zero;
		double alpha  = (i < alphaList.size())  ? alphaList[i] : 1;

		button->getRegion().drawShadow(offset, BLUR_RADIUS, SHADOW_SPREAD, _colorMap.find(button->getKey())->second);
		TextureAsset(button->getKey()).draw(button->getRegion().tl + offset, AlphaF(alpha));

		++i;
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
