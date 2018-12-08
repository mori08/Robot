#include "TitleScene.h"
#include "../Input/InputManager.h"


namespace
{
	const Color BLACK(15);  // 黒
	const Color GRAY(125);  // 灰
	const Color WHITE(240); // 白

	const String ENTER_KEY(L"enter"); // 始めるボタンのキー
	const String EXIT_KEY(L"exit");   // 終えるボタンのキー

	const Point ENTER_BUTTON_POS(420, 300); // 始めるボタンの座標
	const Point EXIT_BUTTON_POS(420, 370);  // 終えるボタンの座標

	const Size  BUTTON_SIZE(160, 70);       // ボタンのサイズ

	const Point TITLE_LOGO_POS(80, 120); // タイトルロゴの座標

	const double SHADOW_BLUR_RADIUS = 20.0; // 影のぼかしの大きさ
	const double SHADOW_SPREAD      = 8.0;  // 影の広がりかた
}


Robot::TitleScene::TitleScene()
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
	Optional<String> selectButtonkey = InputManager::Instance().selectButton();
}


void Robot::TitleScene::draw() const
{
	Window::ClientRect().draw(Color(BLACK));

	Rect(TITLE_LOGO_POS, TextureAsset(L"TitleLogo").size).drawShadow(Vec2::Zero, SHADOW_BLUR_RADIUS, SHADOW_SPREAD, GRAY);
	TextureAsset(L"TitleLogo").draw(TITLE_LOGO_POS);
	
	InputManager::Instance().getSelectedButton().getRegion().drawFrame(1, 1, WHITE);
}
