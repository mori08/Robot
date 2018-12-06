#include "MouseInputState.h"

namespace
{
	const double STOP_RANGE = 100;
}


bool Robot::MouseInputState::decesion() const
{
	return Input::MouseL.released;
}


bool Robot::MouseInputState::option() const
{
	return Input::MouseR.released;
}


Point Robot::MouseInputState::direction() const
{
	Point sub = Mouse::Pos() - Window::Center();

	if (sub.length() < STOP_RANGE)
	{
		return Point::Zero;
	}

	if (sub.y < sub.x && sub.y < -sub.x)
	{
		return std::move(Point::Up);
	}

	if (sub.y > sub.x && sub.y > -sub.x)
	{
		return std::move(Point::Down);
	}

	if (sub.y > sub.x && sub.y < -sub.x)
	{
		return std::move(Point::Left);
	}

	if (sub.y < sub.x && sub.y > -sub.x)
	{
		return std::move(Point::Right);
	}
}


Optional<String> Robot::MouseInputState::selectButton(ButtonPtr & selectedButton, const ButtonList & buttonList) const
{
#ifdef _DEBUG

	if (buttonList.empty())
	{
		Println(L"Error > selectButton‚ÅbuttonList‚ª‹ó‚Å‚·B");
		return none;
	}

#endif // _DEBUG

	for (auto itr = buttonList.begin(); itr != buttonList.end(); ++itr)
	{
		if (!itr->second->getRegion().mouseOver) { continue; }

		selectedButton = itr->second;

		if (decesion()) { return itr->first; }

		return none;
	}

	return none;
}


Optional<String> Robot::MouseInputState::changeState(std::unique_ptr<InputState>& inputState) const
{
	if (Input::AnyKeyClicked)
	{
		return L"KeyInputState";
	}

	return none;
}
