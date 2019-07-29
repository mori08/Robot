#pragma once


#include "DoctorSwitch.h"


namespace Robot
{
	/*
	LockKeyクラス
	LockGoalクラスで使用する
	Playerがこのオブジェクトに触れた時
	LockGoalの変更をする
	*/
	class LockKey : public DoctorSwitch
	{
	private:

		Vec2 _goal; // 目的地

	public:

		LockKey(const Vec2 & pos);

	private:

		Vec2 getMoveVec(GameManager &);

	};

}