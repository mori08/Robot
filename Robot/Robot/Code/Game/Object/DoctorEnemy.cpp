#include "DoctorEnemy.h"


namespace
{
	const double CLEAR_DISTANCE = 5.0; // �N���A���肪�s���鋗��
	const Size   TEXTURE_SIZE(40, 40); // �摜�̃T�C�Y
	const int    CHANGE_TEXTURE_SPAN = 10;  // �摜��ύX����t���[����

	const double SPEED        = 0.2;  // �S�[���̈ړ��̑���

	const int    DEFENCE_NUM  = 4;    // DoctorDefence�̐�
	const double RADIAN_SPEED = 0.02; // DoctorDefence�̉�]�̊p���x
}

Robot::DoctorEnemy::DoctorEnemy(const Vec2 & pos)
	: GameObject(pos)
	, _frameCount(0)
	, _texturePos()
{
	for (int i = 0; i < DEFENCE_NUM; ++i)
	{
		_defenceList.emplace_back(std::make_unique<DoctorDefence>(_pos));
	}
}


void Robot::DoctorEnemy::update(GameManager & gameManager)
{
	if (++_frameCount%CHANGE_TEXTURE_SPAN == 0)
	{
		_texturePos.x++;
	}

	moveObject(gameManager, SPEED*gameManager.getPath(_pos, gameManager.getPlayerPos()));

	gameManager.setGoalPos(_pos);

	if ((_pos - gameManager.getPlayerPos()).length() < CLEAR_DISTANCE)
	{
		gameManager.gameClear();
	}

	updateDefence(gameManager);
}


void Robot::DoctorEnemy::draw() const
{
	TextureAsset(L"Goal")(_texturePos*TEXTURE_SIZE, TEXTURE_SIZE).drawAt(_pos);

	for (const auto & defence : _defenceList)
	{
		defence->draw();
	}
}


void Robot::DoctorEnemy::updateDefence(GameManager & gameManager)
{
	_defenceRadian += RADIAN_SPEED;
	double radian = _defenceRadian;

	for (auto & defence : _defenceList)
	{
		radian += TwoPi / static_cast<double>(_defenceList.size());
		
		Vec2 p = _pos + (StageData::SIZE) * Vec2(Sin(radian), Cos(radian));

		defence->setDefencePos(p);
		defence->update(gameManager);
	}
}
