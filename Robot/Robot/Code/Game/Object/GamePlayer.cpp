#include "GamePlayer.h"


namespace
{
	const double BASE_VALUE = 1.0; // �v���C���[�̕��������߂邽�߂̊�l
	const double ZERO_LINE = 0.01; // �x�N�g���̑傫����0�Ƃ݂Ȃ���l

	const double RADIUS = 10; // ���a
	const double BLUR   = 10; // �ڂ�����
	const double SPREAD = 10; // �L�����
}


Robot::GamePlayer::GamePlayer(const Vec2 & pos)
	: GameObject(pos)
{
}


void Robot::GamePlayer::update(GameManager & gameManager)
{
	moveObject(gameManager, getMoveVec());
}


void Robot::GamePlayer::draw() const
{
	static int a = 0;
	++a;
	TextureAsset(L"Player")(a / 5 * 40, 0, 40, 40).drawAt(_pos);
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
	
	return (moveVec.length() < ZERO_LINE) ? Vec2::Zero : moveVec.normalize();
}
