#include "DoctorEnemy.h"


namespace
{
	const double CLEAR_DISTANCE = 5.0; // �N���A���肪�s���鋗��
	const Size   TEXTURE_SIZE(40, 40); // �摜�̃T�C�Y
	const int    CHANGE_TEXTURE_SPAN = 10;  // �摜��ύX����t���[����

	const double SPEED        = 0.2;  // �S�[���̈ړ��̑���

	const int    DEFENCE_NUM  = 4;    // DoctorDefence�̐�
	const double RADIAN_SPEED = 0.02; // DoctorDefence�̉�]�̊p���x

	const std::vector<Point> SWITCH_POINT // DoctorSwitch�̍��W
	{
		Point(0                          , 0),
		Point(Robot::StageData::WIDTH - 1, 0),
		Point(Robot::StageData::WIDTH - 1, Robot::StageData::HEIGHT - 1),
		Point(0                          , Robot::StageData::HEIGHT - 1)
	};
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
	for (int i = 0; i < DEFENCE_NUM; ++i)
	{
		_switchList.emplace_back(StageData::centerPosOfCell(SWITCH_POINT[i]));
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

	updateSwitch(gameManager);

	for (auto & enemy : _enemyList) { enemy->update(gameManager); }

	updateDefence(gameManager);
}


void Robot::DoctorEnemy::draw() const
{
	TextureAsset(L"Goal")(_texturePos*TEXTURE_SIZE, TEXTURE_SIZE).drawAt(_pos);

	for (const auto & defence : _defenceList)
	{
		defence->draw();
	}

	for(const auto & sw : _switchList)
	{
		sw.draw();
	}

	for (const auto & enemy : _enemyList) { enemy->draw(); }
}


void Robot::DoctorEnemy::drawLight() const
{
	for (const auto & sw : _switchList)
	{
		sw.drawLight();
	}

	for (const auto & enemy : _enemyList) { enemy->drawLight(); }
}


void Robot::DoctorEnemy::updateDefence(GameManager & gameManager)
{
	if (_defenceList.empty()) { return; }

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


void Robot::DoctorEnemy::updateSwitch(GameManager & gameManager)
{
	for (auto & sw : _switchList)
	{
		sw.update(gameManager);

		if (!sw.checkPlayer(gameManager))
		{
			continue;
		}

		if (_defenceList.empty()) { continue; }

		Vec2 pos = _defenceList.back()->getPos();

		_defenceList.pop_back();

		switch (_enemyList.size())
		{
		case 0:
		case 1:
			_enemyList.emplace_back(std::make_unique<RandomEnemy>(pos));
			break;
		case 2:
			_enemyList.emplace_back(std::make_unique<ChaseEnemy>(pos));
			break;
		case 3:
			_enemyList.emplace_back(std::make_unique<RandomCentipede>(pos));
			break;
		}
	}
}
