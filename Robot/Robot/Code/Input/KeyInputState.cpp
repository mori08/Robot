#include"KeyInputState.h"


bool Robot::KeyInputState::decesion() const
{
	return Input::KeyEnter.released;
}


bool Robot::KeyInputState::option() const
{
	return Input::KeyBackspace.released;
}


Point Robot::KeyInputState::direction() const
{
	if (Input::KeyW.pressed) { return std::move(Point::Up); }
	if (Input::KeyS.pressed) { return std::move(Point::Down); }
	if (Input::KeyA.pressed) { return std::move(Point::Left); }
	if (Input::KeyD.pressed) { return std::move(Point::Right); }

	return Point::Zero;
}


Optional<String> Robot::KeyInputState::selectButton(ButtonPtr & selectedButton, const ButtonList &) const
{
#ifdef _DEBUG

	if (selectedButton == nullptr)
	{
		Println(L"Error > selectButton��button���I������Ă��܂���B");
		return none;
	}

#endif // _DEBUG

	checkAndChangeSelectedButton(Input::KeyW, selectedButton, selectedButton->getAdjacentButton(Button::UP));
	checkAndChangeSelectedButton(Input::KeyS, selectedButton, selectedButton->getAdjacentButton(Button::DOWN));
	checkAndChangeSelectedButton(Input::KeyA, selectedButton, selectedButton->getAdjacentButton(Button::LEFT));
	checkAndChangeSelectedButton(Input::KeyD, selectedButton, selectedButton->getAdjacentButton(Button::RIGHT));

	if (decesion())
	{
		return selectedButton->getKey();
	}

	return none;
}


void Robot::KeyInputState::checkAndChangeSelectedButton(const Key & key, ButtonPtr & selectedButton, const ButtonPtr & adjacentButton) const
{
	if (key.clicked && adjacentButton != nullptr)
	{
		selectedButton = adjacentButton;
	}
}
