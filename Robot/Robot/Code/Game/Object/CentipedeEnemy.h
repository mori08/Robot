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

		void update(GameManager & gameManager) override;

		void draw() const override;

		/// <summary>
		/// �ړI�n�̍��W���擾���܂��B
		/// </summary>
		virtual Vec2 getGoalPos() = 0;

	};
}