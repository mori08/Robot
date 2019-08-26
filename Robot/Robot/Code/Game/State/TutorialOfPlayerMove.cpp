#include "TutorialOfPlayerMove.h"
#include "TutorialOfLightMove.h"
#include "../../MyColor.h"


namespace
{
	const size_t DRAW_TEXT_SPAN = 5;
	const Point  DRAW_TEXT_POS(320, 440);
	const double CHANGE_STATE_DIST = 500;

	const Point WASD_POS(30, 240);
}


Robot::TutorialOfPlayerMove::TutorialOfPlayerMove()
{
	_prePlayerPos   = Window::Center();
	_playerMoveDist = 0;
	_frameCount     = 0;
}


void Robot::TutorialOfPlayerMove::update()
{
	++_frameCount;

	PlayingState::update();

	GameManager::Instance().setLightPos(GameManager::Instance().getPlayerPos());

	_playerMoveDist += (GameManager::Instance().getPlayerPos() - _prePlayerPos).length();
	_prePlayerPos = GameManager::Instance().getPlayerPos();
	
	if (_playerMoveDist > CHANGE_STATE_DIST)
	{
		GameManager::Instance().changeGameState(std::make_unique<TutorialOfLightMove>());
	}
}


void Robot::TutorialOfPlayerMove::draw() const
{
	const size_t drawTextLength = _frameCount / DRAW_TEXT_SPAN;
	String text = L"Ç∆ÇËÇ†Ç¶Ç∏à⁄ìÆÇµÇƒÇ›ÇÊÇ§ÅB\n(WASDÉLÅ[)";

	TextureAsset(L"WASD").draw(WASD_POS, Alpha(0xf0));

	FontAsset(L"20")(text.substr(0, drawTextLength)).drawAt(DRAW_TEXT_POS, Palette::MyWhite);

	PlayingState::draw();
}
