
#include"Main.h"


void Main()
{
	MyApp sceneManager;


	while (System::Update())
	{
		sceneManager.updateAndDraw();
	}
}
