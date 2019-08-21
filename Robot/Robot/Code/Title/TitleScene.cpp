#include "TitleScene.h"
#include "../Input/InputManager.h"
#include "../MyColor.h"


namespace
{
	const String ENTER_KEY(L"enter"); // 始めるボタンのキー
	const String EXIT_KEY(L"exit");   // 終えるボタンのキー

	const Point ENTER_BUTTON_POS(400, 300); // 始めるボタンの座標
	const Point EXIT_BUTTON_POS (400, 370); // 終えるボタンの座標

	const Size  BUTTON_SIZE(210, 70);        // ボタンのサイズ
	const Size  BUTTON_BOARD_SIZE(210, 140); // ボタン二つのサイズ
	const int   BUTTON_BOARD_ALPHA = 40;     // ボタン二つの背景の不透明度
	const Size  CURSOR_SIZE(300, 70);        // 

	const Point TITLE_LOGO_POS(80, 120); // タイトルロゴの座標

	const double SHADOW_BLUR_RADIUS = 20.0; // 影のぼかしの大きさ
	const double SHADOW_SPREAD      = 8.0;  // 影の広がりかた

	const int MAX_GENERATE_FRAME_COUNT = 240; // 光生成までの時間の最大値
	const int MIN_GENERATE_FRAME_COUNT = 60;  // 光生成までの時間の最小値

	const double CURSOR_MOVE_RATE = 0.8; // カーソルが動くときの割合
}


Robot::TitleScene::TitleScene()
	: _generateLightFrameCount(0)
{
	InputManager::Instance().clearButtonList();

	InputManager::Instance().registerButton(ENTER_KEY, Rect(ENTER_BUTTON_POS, BUTTON_SIZE));
	InputManager::Instance().registerButton(EXIT_KEY,  Rect(EXIT_BUTTON_POS , BUTTON_SIZE));

	InputManager::Instance().setVerticalAdjacentButton(ENTER_KEY, EXIT_KEY);

	InputManager::Instance().setSelectedButton(ENTER_KEY);

	_cursor = InputManager::Instance().getSelectedButton().getRegion();
	_cursor.size = CURSOR_SIZE;
}


void Robot::TitleScene::init()
{

}


void Robot::TitleScene::update()
{
#ifdef _DEBUG
	if (Input::KeyT.clicked)
	{
		m_data->sceneInfo = L"TestEvent";
		changeScene(L"LoadEventScene");
	}
#endif // _DEBUG


	if (--_generateLightFrameCount <= 0)
	{
		_lightList.emplace_back(TitleLight::get());

		_generateLightFrameCount = Random(MIN_GENERATE_FRAME_COUNT, MAX_GENERATE_FRAME_COUNT);
	}

	for (auto & light : _lightList)
	{
		light.update();
	}

	Erase_if(_lightList, [](TitleLight & light) {return light.isEraseAble(); });

	Optional<String> selectButtonkey = InputManager::Instance().selectButton();

	if(selectButtonkey)
	{
		if (*selectButtonkey == L"enter")
		{
			changeScene(L"LoadSaveDataScene");
		}
		if (*selectButtonkey == L"exit")
		{
			System::Exit();
		}
	}

	_cursor.pos = CURSOR_MOVE_RATE*_cursor.pos + (1 - CURSOR_MOVE_RATE)*InputManager::Instance().getSelectedButton().getRegion().pos;
}


void Robot::TitleScene::draw() const
{
	Rect(TITLE_LOGO_POS, TextureAsset(L"TitleLogo").size).drawShadow(Vec2::Zero, SHADOW_BLUR_RADIUS, SHADOW_SPREAD, Palette::MyWhite);

	_cursor.drawShadow(Vec2::Zero, SHADOW_BLUR_RADIUS, SHADOW_SPREAD, Palette::MyWhite);

	Color boardColor(Palette::MyWhite, BUTTON_BOARD_ALPHA);
	Rect(ENTER_BUTTON_POS, BUTTON_BOARD_SIZE).drawShadow(Vec2::Zero, SHADOW_BLUR_RADIUS, SHADOW_SPREAD, boardColor);

	for (const auto & light : _lightList)
	{
		light.draw();
	}

	TextureAsset(L"WakeButton").draw(ENTER_BUTTON_POS);
	TextureAsset(L"SleepButton").draw(EXIT_BUTTON_POS);

	TextureAsset(L"TitleLogo").draw(TITLE_LOGO_POS);
}
