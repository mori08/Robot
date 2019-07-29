#include "DoctorSwitch.h"


namespace
{
	const int  TEXTURE_CHANGE_SPAN = 4; // �摜��ύX����Ԋu�̃t���[����
	const Size TEXTURE_SIZE(20, 20);    // �摜�̑傫��

	const Point OFF_TEXTURE_POS(0, 1);  // ��~���̃{�^���̍��W

	const double PLAYER_DISTANCE = 10.0; // �v���C���[�Ƃ̋���

	const double RADIUS             = 30.0; // ���̔��a
	const double SHADOW_BLUR_RADIUS = 20.0; // �e�̂ڂ����̑傫��
	const double SHADOW_SPREAD      = 20.0; // �e�̍L�����
}


Robot::DoctorSwitch::DoctorSwitch(const Vec2 & pos)
	: GameObject(pos)
	, _isPressed(false)
	, _frameCount(0)
	, _texturePos(0,0)
{

}


void Robot::DoctorSwitch::update(GameManager & gameManager)
{
	if (_isPressed) { return; }

	if (++_frameCount % TEXTURE_CHANGE_SPAN == 0)
	{
		_texturePos.x++;
	}

	moveObject(gameManager, getMoveVec(gameManager));
}


void Robot::DoctorSwitch::draw() const
{
	TextureAsset(L"DoctorSwitch")(_texturePos*TEXTURE_SIZE, TEXTURE_SIZE).drawAt(_pos);
}


void Robot::DoctorSwitch::drawLight() const
{
	if (_isPressed) { return; }

	Circle(_pos, RADIUS).drawShadow(Vec2::Zero, SHADOW_BLUR_RADIUS, SHADOW_SPREAD, Palette::MyWhite);
}


bool Robot::DoctorSwitch::checkPlayer(const GameManager & gameManager)
{
	if (_isPressed) { return false; }

	if ((_pos - gameManager.getPlayerPos()).length() < PLAYER_DISTANCE)
	{
		_isPressed  = true;
		_texturePos = OFF_TEXTURE_POS;
		return true;
	}

	return false;
}
