#include "LoadScene.h"


namespace
{
	const int   LOADING_FRAME = 4;     // 一コマにかけるフレーム数
	const int   LOADING_NUM = 6;       // 画像の数
	const Size  LOADING_SIZE(40, 30);  // 画像のサイズ
	const Point LOADING_POS(430, 420); // 描画する座標

	const Point LOADING_TEXT_POS = LOADING_POS + Point(60, 0); // 「Loading」を表示する座標
}


Robot::LoadScene::LoadScene()
	: _isLoading(true)
{
}


Robot::LoadScene::~LoadScene()
{
	if (_loadThread.joinable())
	{
		_loadThread.join();
	}
}


void Robot::LoadScene::init()
{
	_loadThread = std::thread(
		[this]() 
		{
			load();
			_isLoading = false;
		}
	);
}


void Robot::LoadScene::update()
{
	++_frameCount;
	
	if (_isLoading) { return; }

	_loadThread.join();

	complete();
}


void Robot::LoadScene::updateFadeIn(double)
{
	++_frameCount;
}


void Robot::LoadScene::updateFadeOut(double)
{
	++_frameCount;
}


void Robot::LoadScene::draw() const
{
	const int i = (_frameCount % (LOADING_FRAME*LOADING_NUM)) / LOADING_FRAME; // 表示する画像の番号を計算

	TextureAsset(L"Loading")(i*LOADING_SIZE.x, 0, LOADING_SIZE).draw(LOADING_POS);

	FontAsset(L"20")(L"Loading" + String(L"......").substr(0, i)).draw(Point(LOADING_TEXT_POS));
}

void Robot::LoadScene::drawFadeIn(double) const
{
	draw();
}

void Robot::LoadScene::drawFadeOut(double) const
{
	draw();
}
