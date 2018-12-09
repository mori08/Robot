#include "TitleScene.h"
#include "../Input/InputManager.h"


namespace
{
	const Color BLACK(15);  // ��
	const Color GRAY(120);  // �D
	const Color WHITE(240); // ��

	const String ENTER_KEY(L"enter"); // �n�߂�{�^���̃L�[
	const String EXIT_KEY(L"exit");   // �I����{�^���̃L�[

	const Point ENTER_BUTTON_POS(420, 300); // �n�߂�{�^���̍��W
	const Point EXIT_BUTTON_POS(420, 370);  // �I����{�^���̍��W

	const Size  BUTTON_SIZE(160, 70);       // �{�^���̃T�C�Y

	const Point TITLE_LOGO_POS(80, 120); // �^�C�g�����S�̍��W

	const double SHADOW_BLUR_RADIUS = 20.0; // �e�̂ڂ����̑傫��
	const double SHADOW_SPREAD      = 8.0;  // �e�̍L���肩��

	const int MAX_GENERATE_FRAME_COUNT = 120;
	const int MIN_GENERATE_FRAME_COUNT = 30;
}


Robot::TitleScene::TitleScene()
	: _generateLightFrameCount(0)
{
	InputManager::Instance().clearButtonList();

	InputManager::Instance().registerButton(ENTER_KEY, Rect(ENTER_BUTTON_POS, BUTTON_SIZE));
	InputManager::Instance().registerButton(EXIT_KEY,  Rect(EXIT_BUTTON_POS , BUTTON_SIZE));

	InputManager::Instance().setVerticalAdjacentButton(ENTER_KEY, EXIT_KEY);

	InputManager::Instance().setSelectedButton(ENTER_KEY);
}


void Robot::TitleScene::init()
{

}


void Robot::TitleScene::update()
{
	if (--_generateLightFrameCount <= 0)
	{
		_lightList.emplace_back(Light::get());

		_generateLightFrameCount = Random(MIN_GENERATE_FRAME_COUNT, MAX_GENERATE_FRAME_COUNT);
	}

	for (auto & light : _lightList)
	{
		light.update();
	}

	Erase_if(_lightList, [](Light & light) {return light.isEraseAble(); });

	Optional<String> selectButtonkey = InputManager::Instance().selectButton();
}


void Robot::TitleScene::draw() const
{
	Window::ClientRect().draw(Color(BLACK));

	Rect(TITLE_LOGO_POS, TextureAsset(L"TitleLogo").size).drawShadow(Vec2::Zero, SHADOW_BLUR_RADIUS, SHADOW_SPREAD, GRAY);

	for (const auto & light : _lightList)
	{
		light.draw();
	}

	TextureAsset(L"TitleLogo").draw(TITLE_LOGO_POS);
	
	InputManager::Instance().getSelectedButton().getRegion().drawFrame(1, 1, WHITE);
}
