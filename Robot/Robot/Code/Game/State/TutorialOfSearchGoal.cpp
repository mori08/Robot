#include "TutorialOfSearchGoal.h"


namespace
{
	const size_t DRAW_TEXT_SPAN = 5;
	const Point  DRAW_TEXT_POS(320, 440);
}


Robot::TutorialOfSearchGoal::TutorialOfSearchGoal()
{
	_frameCount = 0;
}


void Robot::TutorialOfSearchGoal::update(GameManager & gameManager)
{
	++_frameCount;

	gameManager.updateObjectAndLight();
}


void Robot::TutorialOfSearchGoal::draw(const GameManager & gameManager) const
{
	size_t drawTextLength = _frameCount / DRAW_TEXT_SPAN;
	String text = L"ÉSÅ[ÉãÇíTÇµÇƒÅA\nÇªÇ±Ç…çsÇ¡ÇƒÇ›ÇÊÇ§";

	gameManager.drawObjectAndLight();

	FontAsset(L"20")(text.substr(0, drawTextLength)).drawAt(DRAW_TEXT_POS, Palette::MyWhite);
}
