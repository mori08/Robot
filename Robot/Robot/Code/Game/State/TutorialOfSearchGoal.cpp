#include "TutorialOfSearchGoal.h"
#include "../../MyColor.h"


namespace
{
	const size_t DRAW_TEXT_SPAN = 5;
	const Point  DRAW_TEXT_POS(320, 440);
}


Robot::TutorialOfSearchGoal::TutorialOfSearchGoal()
{
	_frameCount = 0;
}


void Robot::TutorialOfSearchGoal::update()
{
	++_frameCount;

	PlayingState::update();
}


void Robot::TutorialOfSearchGoal::draw() const
{
	size_t drawTextLength = _frameCount / DRAW_TEXT_SPAN;
	String text = L"ゴールを探して、\nそこに行ってみよう";

	FontAsset(L"20")(text.substr(0, drawTextLength)).drawAt(DRAW_TEXT_POS, Palette::MyWhite);

	PlayingState::draw();
}
