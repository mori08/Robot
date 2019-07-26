#pragma once


#include"EnemyBase.h"


namespace Robot
{
	/*
	FlashEnemy�N���X
	�����������ƃv���C���[��ǂ�������
	*/
	class FlashEnemy : public EnemyBase
	{
	private:

		int  _changeMoveFramecount; // �s���p�^�[�������̒l�ɉ����ĕύX

		Vec2 _goalPos;              // �������łȂ��Ƃ��̖ړI�n

	public:

		FlashEnemy(const Vec2 & pos);

	private:

		Vec2 getMoveVec(GameManager & gameManager) override;

		void drawLight() const;

	};
}