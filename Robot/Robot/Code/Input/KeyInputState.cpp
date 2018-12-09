#include"KeyInputState.h"


bool Robot::KeyInputState::decesion() const
{
	return Input::KeyEnter.released;
}


bool Robot::KeyInputState::option() const
{
	return Input::KeyBackspace.released;
}


const Point & Robot::KeyInputState::direction() const
{
	if (Input::KeyW.pressed) { return Point::Up; }
	if (Input::KeyS.pressed) { return Point::Down; }
	if (Input::KeyA.pressed) { return Point::Left; }
	if (Input::KeyD.pressed) { return Point::Right; }

	return Point::Zero;
}


Optional<String> Robot::KeyInputState::selectButton(ButtonPtr & selectedButton, const ButtonList &) const
{
#ifdef _DEBUG

	if (selectedButton == nullptr)
	{
		Println(L"Error > selectButton‚Åbutton‚ª‘I‘ð‚³‚ê‚Ä‚¢‚Ü‚¹‚ñB");
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


Optional<String> Robot::KeyInputState::changeState() const
{
	if (Input::MouseL.clicked || Input::MouseR.clicked)
	{
		return L"MouseInputState";
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
