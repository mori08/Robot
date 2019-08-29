#include "SavingDataScene.h"
#include "SaveDataManager.h"
#include "../Menu/MenuManager.h"


namespace
{
	const int   LOADING_FRAME = 4;     // 一コマにかけるフレーム数
	const int   LOADING_NUM = 6;       // 画像の数
	const Size  LOADING_SIZE(40, 30);  // 画像のサイズ
	const Point LOADING_POS(430, 420); // 描画する座標

	const Point LOADING_TEXT_POS = LOADING_POS + Point(60, 0); // 「Loading」を表示する座標
}


void Robot::SavingDataScene::load()
{
	SaveDataManager::Instance().save();
}


void Robot::SavingDataScene::complete()
{
	changeScene(L"LoadMenuScene");
}


void Robot::SavingDataScene::draw() const
{
	const int i = (_frameCount % (LOADING_FRAME*LOADING_NUM)) / LOADING_FRAME; // 表示する画像の番号を計算

	TextureAsset(L"Loading")(i*LOADING_SIZE.x, 0, LOADING_SIZE).draw(LOADING_POS);

	FontAsset(L"20")(L"Saving" + String(L"......").substr(0, i)).draw(Point(LOADING_TEXT_POS));
}
