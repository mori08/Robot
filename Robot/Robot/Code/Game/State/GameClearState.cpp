#include "GameClearState.h"


namespace
{
	const int BACK_ALPHA_SPEED  = 15;  // �w�i�̓����x��1�t���[���ŕύX����l
	const int LIGHT_ALPHA_SPEED = 25;  // ���̓����x��1�t���[���ŕύX����l
	const int ALPHA_MAX         = 255; // �s�����x�̍ő�l

	const int LIGHT_START_FRAME_COUNT  = 60;  // ����`�悵�n�߂�t���[����
	const int CHANGE_SCENE_FRAME_COUNT = 200; // �V�[���J�ڂ��s���t���[����

	const Size      LIGHT_SIZE(450, 110);                                 // ���̃T�C�Y
	const Rect      LIGHT_RECT(Point(320, 240)-LIGHT_SIZE/2, LIGHT_SIZE); // ���̎l�p
	const RoundRect LIGHT_ROUNDRECT(LIGHT_RECT, 50);                      // ���S�ɕ\�����n�߂鎞��
	const double BLUR_RADIUS   = 50.0; // �e�̂ڂ�����
	const double SHADOW_SPREAD = 15.0; // �e�̍L�����

	const int    SMALL_LIGHT_NUM       = 12;   // �����Ȍ����Ȃ��p�x
	const double SMALL_LIGHT_MOVE_RATE = 0.97; // �����Ȍ��̈ړ��̊���
	const double SMALL_LIGHT_DIST_MAX  = 300;  // �����Ȍ��̍ő�ړ�����
}


Robot::GameClearState::GameClearState()
	: _frameCount(0)
	, _backColor(Palette::MyBlack, 0)
	, _lightColor(Palette::MyWhite, 0)
{
	// 360�x�̑S���������X�g�ɒǉ�
	for (int i = 0; i < SMALL_LIGHT_NUM; ++i)
	{
		double radian = 2 * Pi*i / SMALL_LIGHT_NUM;
		_smallLightDirectionList.emplace_back(Cos(radian), Sin(radian));
	}
}


void Robot::GameClearState::update(GameManager & gameManager)
{
	++_frameCount;

	addAlpha(_backColor, BACK_ALPHA_SPEED);

	if (_frameCount < LIGHT_START_FRAME_COUNT) { return; }

	addAlpha(_lightColor, LIGHT_ALPHA_SPEED);

	_smallLightDist = SMALL_LIGHT_MOVE_RATE*_smallLightDist + (1 - SMALL_LIGHT_MOVE_RATE)*SMALL_LIGHT_DIST_MAX;

	if (_frameCount > CHANGE_SCENE_FRAME_COUNT)
	{
		gameManager.setSceneName(L"MenuScene", L"");
	}
}


void Robot::GameClearState::draw(const GameManager & gameManager) const
{
	gameManager.drawObjectAndLight();

	Window::ClientRect().draw(_backColor);

	if (_frameCount < LIGHT_START_FRAME_COUNT) { return; }

	LIGHT_ROUNDRECT.drawShadow(Vec2::Zero, BLUR_RADIUS, SHADOW_SPREAD, _lightColor);

	for (const auto & d : _smallLightDirectionList)
	{
		Circle(Window::Center() + d*_smallLightDist).drawShadow(Vec2::Zero, BLUR_RADIUS, SHADOW_SPREAD, _lightColor);
	}

	TextureAsset(L"Success").drawAt(Window::Center());
}


void Robot::GameClearState::addAlpha(Color & color, int addValue)
{
	if (color.a + addValue > ALPHA_MAX)
	{
		color.a = ALPHA_MAX;
		return;
	}

	color.a += addValue;
}
