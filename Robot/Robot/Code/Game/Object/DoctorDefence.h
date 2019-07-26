#pragma once


#include "EnemyBase.h"


namespace Robot
{
	/*
	DoctorDefence�N���X
	DoctorGoal�N���X�̎��͂��܂��
	�v���C���[��DoctorGoal�ɋ߂Â�����ǐՂ���
	*/
	class DoctorDefence : public EnemyBase
	{
	private :

		Vec2 _defencePos; // �S�[������邽�߂̈ʒu

	public:

		DoctorDefence(const Vec2 & pos);

		/// <summary>
		/// _defencePos�̐ݒ�
		/// </summary>
		/// <param name="pos"> ���W </param>
		void setDefencePos(const Vec2 & pos);



	private:

		Vec2 getMoveVec(GameManager & gameManager) override;

	};

}