#include "GamePlayer.h"


namespace
{
	const double BASE_VALUE = 1.0; // �v���C���[�̕��������߂邽�߂̊�l
	const double ZERO_LINE = 0.01; // �x�N�g���̑傫����0�Ƃ݂Ȃ���l

	const double RADIUS = 10; // ���a
	const double BLUR   = 10; // �ڂ�����
	const double SPREAD = 10; // �L�����

	const Size TEXTURE_SIZE(40, 40);      // �摜�T�C�Y
	const int  CHEANGE_TEXTURE_SPAN = 60; // �摜��ύX����p�x

	const double CHANGE_RATE            = 0.95;  // _lightCircleRate��ύX���銄��
	const double RATE_MIN               = 0.001; // _lightCircleRate�̍ŏ��l
	const double LIGHT_CIRCLE_RADIUS    = 40;    // ���̗ւ̔��a
	const double LIGHT_CIRCLE_THICKNESS = 1;     // ���̗ւ̌���

	const double SPEED = 1.2;
}


Robot::GamePlayer::GamePlayer(const Vec2 & pos)
	: GameObject(pos)
{
}


void Robot::GamePlayer::update(GameManager & gameManager)
{
	_lightCircleRate *= CHANGE_RATE;
	if (_lightCircleRate < RATE_MIN) { _lightCircleRate = 1; }

	moveObject(gameManager, getMoveVec());

	gameManager.setPlayerPos(_pos);
}


void Robot::GamePlayer::draw() const
{
	ColorF lightColor(Palette::MyWhite);
	lightColor.setAlpha(Sqrt(_lightCircleRate));
	Circle(_pos, (1 - _lightCircleRate)*LIGHT_CIRCLE_RADIUS).drawFrame(LIGHT_CIRCLE_THICKNESS, LIGHT_CIRCLE_THICKNESS, lightColor);

	TextureAsset(L"Player").drawAt(_pos);
}


Vec2 Robot::GamePlayer::getMoveVec() const
{
	Vec2 moveVec = Vec2::Zero;

	if (Input::KeyA.pressed)
	{
		moveVec.x -= BASE_VALUE;
	}

	if (Input::KeyD.pressed)
	{
		moveVec.x += BASE_VALUE;
	}

	if (Input::KeyW.pressed)
	{
		moveVec.y -= BASE_VALUE;
	}

	if (Input::KeyS.pressed)
	{
		moveVec.y += BASE_VALUE;
	}
	
	return (moveVec.length() < ZERO_LINE) ? Vec2::Zero : SPEED*moveVec.normalize();
}
