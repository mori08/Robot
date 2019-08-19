#pragma once


#include "DoctorSwitch.h"


namespace Robot
{
	/*
	LockKey�N���X
	LockGoal�N���X�Ŏg�p����
	Player�����̃I�u�W�F�N�g�ɐG�ꂽ��
	LockGoal�̕ύX������
	*/
	class LockKey : public DoctorSwitch
	{
	private:

		Vec2 _goal; // �ړI�n

	public:

		LockKey(const Vec2 & pos);

	private:

		Vec2 getMoveVec();

	};

}