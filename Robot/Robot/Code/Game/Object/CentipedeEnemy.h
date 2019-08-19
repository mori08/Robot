#pragma once


#include "CentipedeBody.h"


namespace Robot
{
	/*
	CentipedeEnemy�N���X
	���J�f�^�̓G
	CentipedeBody�̃��X�g���X�V�E�`����s��
	*/
	class CentipedeEnemy : public GameObject
	{
	protected:

		std::vector<std::unique_ptr<CentipedeBody>> _bodyList; // �̂̃p�[�c���X�g

	public:

		CentipedeEnemy(const Vec2 & pos)
			: GameObject(pos)
		{
		}

		void update() override;

		void draw() const override;

	protected:

		/// <summary>
		/// �ړI�n�̍��W���擾���܂��B
		/// </summary>
		virtual Vec2 getGoalPos() = 0;

	};
}