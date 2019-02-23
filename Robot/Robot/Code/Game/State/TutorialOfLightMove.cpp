#include "TutorialOfLightMove.h"
#include "TutorialOfSearchGoal.h"


namespace
{
	const int CHANGE_STATE_FRAMECOUNT = 20 * 60;
	const Point  DRAW_TEXT_POS(320, 460);
	const size_t DRAW_TEXT_SPAN = 5;
}


Robot::TutorialOfLightMove::TutorialOfLightMove()
	: _frameCount(0)
{

}


void Robot::TutorialOfLightMove::update(GameManager & gameManager)
{
	++_frameCount;

	gameManager.updateObjectAndLight();

	if (_frameCount > CHANGE_STATE_FRAMECOUNT)
	{
		gameManager.makeTutorialGoal();
		gameManager.changeGameState(std::make_unique<TutorialOfSearchGoal>());
	}
}


void Robot::TutorialOfLightMove::draw(const GameManager & gameManager) const
{
	size_t drawTextLength = _frameCount / DRAW_TEXT_SPAN;
	String text = L"�}�E�X�Ō��𑀍삵�Ă�������";

	gameManager.drawObjectAndLight();

	FontAsset(L"20")(text.substr(0, drawTextLength)).drawAt(DRAW_TEXT_POS, Palette::MyWhite);
}
