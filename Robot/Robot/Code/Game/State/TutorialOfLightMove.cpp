#include "TutorialOfLightMove.h"
#include "TutorialOfSearchGoal.h"
#include "../../MyColor.h"


namespace
{
	const int CHANGE_STATE_FRAMECOUNT = 10 * 60;
	const Point  DRAW_TEXT_POS(320, 440);
	const size_t DRAW_TEXT_SPAN = 5;

	const Point MOUSE_POS(30, 240);
}


Robot::TutorialOfLightMove::TutorialOfLightMove()
	: _frameCount(0)
{

}


void Robot::TutorialOfLightMove::update()
{
	++_frameCount;

	PlayingState::update();

	if (_frameCount > CHANGE_STATE_FRAMECOUNT)
	{
		GameManager::Instance().makeTutorialGoal();
		GameManager::Instance().changeGameState(std::make_unique<TutorialOfSearchGoal>());
	}
}


void Robot::TutorialOfLightMove::draw() const
{
	size_t drawTextLength = _frameCount / DRAW_TEXT_SPAN;
	String text = L"今度は光を動かしてみよう。(マウス)";

	TextureAsset(L"Mouse").draw(MOUSE_POS, Alpha(0xF0));

	FontAsset(L"20")(text.substr(0, drawTextLength)).drawAt(DRAW_TEXT_POS, Palette::MyWhite);

	PlayingState::draw();
}
