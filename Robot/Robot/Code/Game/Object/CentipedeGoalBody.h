#pragma once


#include "CentipedeBody.h"


namespace Robot
{
	/*
	CentipedeBody�N���X
	CentipedeEnemy�̕��i
	�G�ł͂Ȃ��S�[���Ƃ��Ă̋@�\����������
	*/
	class CentipedeGoalBody : public CentipedeBody
	{
	public:

		/// <summary>
		/// �S�[���Ƃ��Ă̋@�\���郀�J�f�^�̓G�̕��i
		/// </summary>
		/// <param name="pos"> �������W </param>
		CentipedeGoalBody(const Vec2 & pos);

	private:

		void draw() const override;

		void connectedPlayerProcess(GameManager & gameManager) override;

	};
}