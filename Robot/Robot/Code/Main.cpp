
#include"MyLibrary.h"
#include"MyColor.h"
#include"Input\InputManager.h"
#include"Title\TitleScene.h"
#include"SaveData\LoadSaveDataScene.h"
#include"Event\EventScene.h"
#include"Event\LoadEventScene.h"
#include"Event\EventManager.h"
#include"Event\Factor\GenerateEvent.h"
#include"Game\GameScene.h"
#include"Game\LoadGameScene.h"
#include"Menu\MenuScene.h"
#include"Game\GameManager.h"
#include"SaveData\SavingDataScene.h"
#include"SaveData\ResetSaveDataScene.h"


void Main()
{
	// ウィンドウのタイトルの設定
	Window::SetTitle(L"556");

	// 背景色の設定
	Graphics::SetBackground(Robot::Palette::MyBlack);

	// 画像をアセット管理
	Robot::asseter(L"Asset/");

	// フォントのアセット管理
	FontAsset::Register(L"15", 15, L"メイリオ");
	FontAsset::Register(L"20", 20, L"メイリオ");

	// 各クラスの準備
	Robot::GenerateEvent::setObjectMap();
	Robot::EventManager::Instance().setAllEvent();
	Robot::GameManager::Instance().setObjMap();

	// シーンの準備
	MyApp sceneManager;
	sceneManager.add<Robot::TitleScene>        (L"TitleScene");
	sceneManager.add<Robot::LoadSaveDataScene> (L"LoadSaveDataScene");
	sceneManager.add<Robot::LoadEventScene>    (L"LoadEventScene");
	sceneManager.add<Robot::EventScene>        (L"EventScene");
	sceneManager.add<Robot::GameScene>         (L"GameScene");
	sceneManager.add<Robot::LoadGameScene>     (L"LoadGameScene");
	sceneManager.add<Robot::MenuScene>         (L"MenuScene");
	sceneManager.add<Robot::SavingDataScene>   (L"SavingDataScene");
	sceneManager.add<Robot::ResetSaveDataScene>(L"ResetSaveDataScene");

	while (System::Update())
	{
		sceneManager.updateAndDraw();

		Robot::InputManager::Instance().changeState();

#ifdef _DEBUG
		FontAsset(L"15")(Profiler::FPS()).draw(Point::Zero, Palette::Red);
#endif // _DEBUG

	}
}
