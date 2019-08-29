#include "TitleScene.h"
#include "../Input/InputManager.h"
#include "../MyColor.h"
#include "../SaveData/SaveDataManager.h"


namespace
{
	const String NEWGAME_KEY (L"NEWGAME" ); // はじめからボタンのキー
	const String CONTINUE_KEY(L"CONTINUE"); // つづきからボタンのキー
	const String EXIT_KEY    (L"EXIT");     // やめるボタンのキー
	const std::vector<String> KEY_LIST      // キーのリスト
	{
		NEWGAME_KEY,
		CONTINUE_KEY,
		EXIT_KEY
	};

	const Point BUTTON_POS(510, 380); // 一番上のボタンの座標
	const int   BUTTON_WIDTH(200);    // ボタンの幅

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

	Rect region(BUTTON_POS, BUTTON_WIDTH, FontAsset(L"15").height);
	for (const auto & key : KEY_LIST)
	{
		InputManager::Instance().registerButton(key, region);
		region.y += FontAsset(L"15").height;
	}

	InputManager::Instance().setVerticalAdjacentButton(NEWGAME_KEY , CONTINUE_KEY);
	InputManager::Instance().setVerticalAdjacentButton(CONTINUE_KEY, EXIT_KEY    );

	InputManager::Instance().setSelectedButton(CONTINUE_KEY);

	_cursor = InputManager::Instance().getSelectedButton().getRegion();
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
		if (*selectButtonkey == NEWGAME_KEY)
		{
			SaveDataManager::Instance().initOfNewGame();
			m_data->sceneInfo = L"Stage0Start";
			changeScene(L"LoadEventScene");
		}
		if (*selectButtonkey == CONTINUE_KEY)
		{
			changeScene(L"LoadSaveDataScene");
		}
		if (*selectButtonkey == EXIT_KEY)
		{
			System::Exit();
		}
	}

	_cursor.pos = CURSOR_MOVE_RATE*_cursor.pos + (1 - CURSOR_MOVE_RATE)*InputManager::Instance().getSelectedButton().getRegion().pos;
}


void Robot::TitleScene::updateFadeOut(double)
{
	for (auto & light : _lightList)
	{
		light.update();
	}

	_cursor.pos = CURSOR_MOVE_RATE*_cursor.pos + (1 - CURSOR_MOVE_RATE)*InputManager::Instance().getSelectedButton().getRegion().pos;
}


void Robot::TitleScene::draw() const
{
	Rect(TITLE_LOGO_POS, TextureAsset(L"TitleLogo").size).drawShadow(Vec2::Zero, SHADOW_BLUR_RADIUS, SHADOW_SPREAD, Palette::MyWhite);

	for (const auto & light : _lightList)
	{
		light.draw();
	}

	Color boardColor(Palette::MyBlack, 0x80);
	Rect(BUTTON_POS, BUTTON_WIDTH, (int)KEY_LIST.size()*FontAsset(L"15").height).drawShadow(Vec2::Zero, SHADOW_BLUR_RADIUS, SHADOW_SPREAD, boardColor);

	_cursor.draw(Palette::MyWhite);

	int y = BUTTON_POS.y;
	for (const auto & key : KEY_LIST)
	{
		Color color = key == InputManager::Instance().getSelectedButton().getKey() ? Palette::MyBlack : Palette::MyWhite;
		FontAsset(L"15")(key).draw(Window::Width() - FontAsset(L"15")(key).region().w - 10, y, color);
		y += FontAsset(L"15").height;
	}

	TextureAsset(L"TitleLogo").draw(TITLE_LOGO_POS);
}
