#pragma once


#include "EnemyBase.h"


namespace Robot
{
	/*
	GiantEnemy�N���X
	����ȓG
	*/
	class GiantEnemy : public EnemyBase
	{
	private:

		int   _frameCount; // �o�߃t���[����

		Point _texturePos; // �`�悷��摜�̔ԍ�

		Vec2  _goalPos;    // �ړI���W

	public:

		/// <sumamry>
		/// ����ȓG
		/// </summary>
		/// <param name="pos"> �������W </param>
		GiantEnemy(const Vec2 & pos);

	private:

		void update(GameManager & gameManager) override;

		void draw() const override;

		Vec2 getMoveVec(GameManager & gameManager) override;

	};
}