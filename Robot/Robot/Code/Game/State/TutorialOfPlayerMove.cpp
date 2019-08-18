#include "TutorialOfPlayerMove.h"
#include "TutorialOfLightMove.h"


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


void Robot::TutorialOfPlayerMove::update(GameManager & gameManager)
{
	++_frameCount;

	gameManager.updateObjectAndLight();

	gameManager.setLightPos(gameManager.getPlayerPos());

	_playerMoveDist += (gameManager.getPlayerPos() - _prePlayerPos).length();
	_prePlayerPos = gameManager.getPlayerPos();
	
	if (_playerMoveDist > CHANGE_STATE_DIST)
	{
		gameManager.changeGameState(std::make_unique<TutorialOfLightMove>());
	}
}


void Robot::TutorialOfPlayerMove::draw(const GameManager & gameManager) const
{
	const size_t drawTextLength = _frameCount / DRAW_TEXT_SPAN;
	String text = L"Ç∆ÇËÇ†Ç¶Ç∏à⁄ìÆÇµÇƒÇ›ÇÊÇ§ÅB\n(WASDÉLÅ[)";

	gameManager.drawObjectAndLight();

	TextureAsset(L"WASD").draw(WASD_POS, Alpha(0xf0));

	FontAsset(L"20")(text.substr(0, drawTextLength)).drawAt(DRAW_TEXT_POS, Palette::MyWhite);
}
