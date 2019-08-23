#include "CentipedeEnemy.h"
#include "../../MyColor.h"


namespace
{
	const size_t LEADER_INDEX  = 0;  // �擪�̃C���f�b�N�X
	const size_t BODY_DISTANCE = 40; // �̂̕��i���ۂ���

	const double RADIUS             = 30.0; // ���̔��a
	const double SHADOW_BLUR_RADIUS = 10.0; // �e�̂ڂ����̑傫��
	const double SHADOW_SPREAD      = 10.0; // �e�̍L�����
}


void Robot::CentipedeEnemy::update()
{
	// �擪��getGoalPos�֐��Ŏw�肳�ꂽ�ړI�n�ֈړ�
	if (GameManager::Instance().isWalkingAblePos(getGoalPos()))
	{
		_bodyList[LEADER_INDEX]->setGoalPos(getGoalPos());
	}

	for (int i = 1; i < _bodyList.size(); ++i)
	{
		// �������O�̓G��ǐ�
		if ((_bodyList[i]->getPos() - _bodyList[i-1]->getPos()).length() < BODY_DISTANCE)
		{
			continue;
		}
		_bodyList[i]->setGoalPos(_bodyList[i - 1]->getPos());
	}

	for (auto && body : _bodyList)
	{
		body->update();
	}
}


void Robot::CentipedeEnemy::draw() const
{
	for (const auto & body : _bodyList)
	{
		body->draw();
	}
}


void Robot::CentipedeEnemy::drawLight() const
{
	Circle(_bodyList[LEADER_INDEX]->getPos(), RADIUS).drawShadow(Vec2::Zero, SHADOW_BLUR_RADIUS, SHADOW_SPREAD, Color(Palette::MyWhite, 0x50));
}
