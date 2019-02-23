#pragma once


#include "EnemyBase.h"


namespace Robot
{
	/*
	CentipedeBody�N���X
	CentipedeEnemy�̕��i
	�ړI�n��ݒ肵�Ă����ǂ킹��
	*/
	class CentipedeBody : public GameObject
	{
	protected:

		Vec2 _goalPos;    // �ړI���W

		int  _frameCount; // �o�߃t���[����

	public:

		/// <summary>
		/// CentipedeEnemy�̕��i
		/// </summary>
		/// <param name="pos"> �ړI���W </para,>
		CentipedeBody(const Vec2 & pos);

		void update(GameManager & gameManager) override;

		virtual void draw() const override;

		/// <summary>
		/// ���W���擾���܂��B
		/// </summary>
		const Vec2 & getPos() const
		{
			return _pos;
		}

		/// <summary>
		/// �ړI���W��ݒ肵�܂��B
		/// </summary>
		/// <param name="pos"> ���W </param>
		void setGoalPos(const Vec2 & pos)
		{
			_goalPos = pos;
		}

	protected:

		/// <summary>
		/// �v���C���[�ƐڐG�����Ƃ��̏���
		/// </summary>
		/// <param name="gameManager"> GameManager�̃C���X�^���X </param>
		virtual void connectedPlayerProcess(GameManager & gameManager);

	};
}