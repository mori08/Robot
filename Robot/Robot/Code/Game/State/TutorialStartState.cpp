#include "TutorialStartState.h"
#include "TutorialOfPlayerMove.h"
#include "../../MyColor.h"


namespace
{
	const size_t DRAW_TEXT_SPAN = 5;
	const Point  DRAW_TEXT_POS(320, 460);
	const int    CHANGE_STATE_FRAMECOUNT = 300;
}


void Robot::TutorialStartState::update()
{
	++_framecount;

	GameManager::Instance().updateObjectAndLight();

	GameManager::Instance().setLightPos(GameManager::Instance().getPlayerPos());

	if (_framecount > CHANGE_STATE_FRAMECOUNT)
	{
		GameManager::Instance().changeGameState(std::make_unique<TutorialOfPlayerMove>());
	}
}


void Robot::TutorialStartState::draw() const
{
	const size_t drawTextLength = _framecount / DRAW_TEXT_SPAN;
	String text = L"ここがテレビの中かな…。";

	GameManager::Instance().drawObjectAndLight();

	FontAsset(L"20")(text.substr(0, drawTextLength)).drawAt(DRAW_TEXT_POS, Palette::MyWhite);
}
