#include "LoseState.h"
#include "../../SaveData/SaveDataManager.h"
#include "../../MyColor.h"


namespace
{
	const int CELL_ALPHA_SPEED = 15; // �}�X�̓����x��1�t���[���ŕύX����l
	const int BACK_ALPHA_SPEED = 15; // �w�i�̓����x��1�t���[���ŕύX����l

	const int ALPHA_MAX = 255; // �s�����x�̍ő�l

	const Size CELL_SIZE(40, 40); // 1�}�X�̑傫��

	const int TEXT_DRAW_FRAME_COUNT = 40;      // �e�L�X�g��\�����n�߂�t���[����
	const int SCENE_FRAME_COUNT     = 600;     // �V�[���J�ڂ���t���[����

	const int TEXT_DRAW_SPAN = 12; // �e�L�X�g��\������t���[����
	const int CHAR_WIDTH     = 64; // 1�����̕�
}


Robot::LoseState::LoseState()
	: _frameCount(0)
	, _cellColor(Palette::MyBlack, 0)
	, _backColor(Palette::MyWhite, 0)
	,_textDrawRegion(16, 112)
{
}


void Robot::LoseState::update()
{
	++_frameCount;

	addAlpha(_cellColor, CELL_ALPHA_SPEED);

	if (_frameCount < TEXT_DRAW_FRAME_COUNT) { return; }

	addAlpha(_backColor, BACK_ALPHA_SPEED);

	if (_frameCount%TEXT_DRAW_SPAN == 0)
	{
		_textDrawRegion.x += CHAR_WIDTH;
	}

	if (_frameCount < SCENE_FRAME_COUNT) { return; }

	if (SaveDataManager::Instance().getFlag(GameManager::Instance().getStageName()))
	{
		GameManager::Instance().setSceneName(L"SavingDataScene", L"");
	}
	else
	{
		GameManager::Instance().setSceneName(L"LoadEventScene", GameManager::Instance().getStageName() + L"End");
	}

	SaveDataManager::Instance().setFlag(GameManager::Instance().getStageName(), true);
}


void Robot::LoseState::draw() const
{
	static const Rect SHAKE_RANGE(-1, -1, 2, 2); // �U���͈̔�

	Window::ClientRect().draw(Palette::MyWhite);

	for (int x = 0; x < Window::Width(); x += CELL_SIZE.x)
	{
		for (int y = 0; y < Window::Height(); y += CELL_SIZE.y)
		{
			Rect(Point(x, y) + RandomPoint(SHAKE_RANGE), CELL_SIZE).draw(_cellColor);
		}
	}

	TextureAsset(L"Failed")(Point::Zero, _textDrawRegion).drawAt(Window::Center());
}

void Robot::LoseState::addAlpha(Color & color, int addValue)
{
	if (color.a + addValue > ALPHA_MAX)
	{
		color.a = ALPHA_MAX;
		return;
	}

	color.a += addValue;
}
