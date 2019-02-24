#include "GameOverState.h"
#include "../../Input/InputManager.h"


namespace
{
	const int CELL_ALPHA_SPEED = 15; // �}�X�̓����x��1�t���[���ŕύX����l
	const int BACK_ALPHA_SPEED = 15; // �w�i�̓����x��1�t���[���ŕύX����l

	const int ALPHA_MAX = 255; // �s�����x�̍ő�l

	const Size CELL_SIZE(40, 40); // 1�}�X�̑傫��

	const int TEXT_DRAW_FRAME_COUNT = 40; // �U������t���[����
	const int SELCT_FRAME_COUNT = 120;    // �I�������ł�t���[����

	const int TEXT_DRAW_SPAN = 12; // �e�L�X�g��\������t���[����
	const int CHAR_WIDTH     = 64; // 1�����̕�
	const int TEXT_LENGTH    = 5;  // ������

	const String RETRY_KEY(L"retry"); // ���g���C�{�^���̃L�[
	const String MENU_KEY (L"menu");  // ���j���[�ɖ߂�{�^���̃L�[

	const Point RETRY_BUTTON_POS(420, 368); // ���g���C�{�^���̍��W
	const Point MENU_BUTTON_POS(420, 424);  // ���j���[�ɖ߂�{�^���̍��W
	const Size  BUTTON_SIZE(168, 56);       // �{�^���̃T�C�Y

	const double CURSOR_MOVE_RATE = 0.8; // �J�[�\���������Ƃ��̊���
}


Robot::GameOverState::GameOverState()
	: _frameCount(0)
	, _cellColor(Palette::MyBlack, 0)
	, _backColor(Palette::MyWhite, 0)
	, _textDrawRegion(12,112)
{
	InputManager::Instance().clearButtonList();

	InputManager::Instance().registerButton(RETRY_KEY, Rect(RETRY_BUTTON_POS, BUTTON_SIZE));
	InputManager::Instance().registerButton(MENU_KEY , Rect(MENU_BUTTON_POS , BUTTON_SIZE));

	InputManager::Instance().setVerticalAdjacentButton(RETRY_KEY, MENU_KEY);

	InputManager::Instance().setSelectedButton(RETRY_KEY);

	_cursor = InputManager::Instance().getSelectedButton().getRegion();
}


void Robot::GameOverState::update(GameManager & gameManager)
{
	++_frameCount;

	addAlpha(_cellColor, CELL_ALPHA_SPEED);

	if (_frameCount < TEXT_DRAW_FRAME_COUNT) { return; }

	addAlpha(_backColor, BACK_ALPHA_SPEED);

	if (_frameCount%TEXT_DRAW_SPAN == 0)
	{
		_textDrawRegion.x += CHAR_WIDTH;
	}

	if (_frameCount < SELCT_FRAME_COUNT) { return; }

	Optional<String> selectButtonkey = InputManager::Instance().selectButton();

	if (selectButtonkey)
	{
		if (*selectButtonkey == RETRY_KEY)
		{
			gameManager.setSceneName(L"LoadGameScene", gameManager.getStageName());
		}
		if (*selectButtonkey == MENU_KEY)
		{
			gameManager.setSceneName(L"MenuScene", L"");
		}
	}

	_cursor.pos = CURSOR_MOVE_RATE*_cursor.pos + (1 - CURSOR_MOVE_RATE)*InputManager::Instance().getSelectedButton().getRegion().pos;
}


void Robot::GameOverState::draw(const GameManager &) const
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

	if (_frameCount < SELCT_FRAME_COUNT) { return; }

	_cursor.draw(Palette::MyWhite);

	TextureAsset(L"ReTryButton").draw(RETRY_BUTTON_POS);
	TextureAsset(L"BackMenuButton").draw(MENU_BUTTON_POS);
}


void Robot::GameOverState::addAlpha(Color & color, int addValue)
{
	if (color.a + addValue > ALPHA_MAX)
	{
		color.a = ALPHA_MAX;
		return;
	}

	color.a += addValue;
}
