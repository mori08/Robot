
#include"Main.h"
#include"Input\InputManager.h"
#include"Title\TitleScene.h"


void Main()
{
	MyApp sceneManager;

	sceneManager.add<Robot::TitleScene>(L"TitleScene");

	while (System::Update())
	{
		sceneManager.updateAndDraw();

		Robot::InputManager::Instance().changeState();
	}
}
