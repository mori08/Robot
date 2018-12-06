
#include"Main.h"
#include"Input\InputManager.h"


void Main()
{
	MyApp sceneManager;


	while (System::Update())
	{
		sceneManager.updateAndDraw();

		Robot::InputManager::Instance().changeState();
	}
}
