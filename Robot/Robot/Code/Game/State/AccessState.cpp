#include "AccessState.h"
#include "PlayingState.h"
#include "TutorialStartState.h"


namespace
{
	const int ALPHA_START_FRAMECOUNT = 180; // アルファ値を変更し始めるフレーム数
	const int ALPHA_SPEED            = 5;   // 

	const Size ICON_SIZE(120, 120);          // 表示するアイコンの

	const Point BOXROBOT_ICON_POS(120, 240); // 箱型ロボットのアイコンを表示する座標
	const Point TARGET_ICON_POS  (520, 240); // ターゲットのアイコンを表示する座標

	const Size ACCESS_LINE_SIZE(240, 60); // ラインのサイズ
}


Robot::AccessState::AccessState(bool isTutorial)
	: _framecount(0)
	, _alpha(0xFF)
	, _stageId(GameManager::Instance().getStageName()[5] - '0')
{
	if (isTutorial)
	{
		_nextState = std::make_unique<TutorialStartState>();
	}
	else
	{
		_nextState = std::make_unique<PlayingState>();
	}
}


void Robot::AccessState::update(GameManager & gameManager)
{
	++_framecount;

	if (_framecount < ALPHA_START_FRAMECOUNT) { return; }

	_alpha = std::max(0, _alpha - ALPHA_SPEED);

	if (_alpha == 0)
	{
		gameManager.changeGameState(std::move(_nextState));
	}

	gameManager.updateObjectAndLight();

	gameManager.setLightPos(gameManager.getPlayerPos());
}


void Robot::AccessState::draw(const GameManager & gameManager) const
{
	gameManager.drawObjectAndLight();

	Window::ClientRect().draw(Color(Palette::MyBlack, _alpha));

	TextureAsset(L"BoxRobotAccess").drawAt(BOXROBOT_ICON_POS, Alpha(_alpha));
	TextureAsset(L"AccessTarget")(_stageId*Point::Right*ICON_SIZE, ICON_SIZE).drawAt(TARGET_ICON_POS,Alpha(_alpha));
	TextureAsset(L"AccessLine")(Point(-_framecount, 0), ACCESS_LINE_SIZE).drawAt(Window::Center(),Alpha(_alpha));
}
