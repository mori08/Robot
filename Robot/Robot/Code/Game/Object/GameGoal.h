#pragma once


#include"../GameManager.h"


namespace Robot
{
	/*
	GameGaol�N���X
	Player�����̃I�u�W�F�N�g�ɐG�ꂽ��
	�N���A�ƂȂ�܂��B
	*/
	class GameGoal : public GameObject
	{
	private:

		int   _frameCount; // �o�߃t���[����

		Point _texturePos; // �\������摜�̔ԍ�

	public:

		/// <summary>
		/// �Q�[���ł̃S�[��
		/// </summary>
		/// <param name="pos"> �������W </param>
		GameGoal(const Vec2 & pos)
			: GameObject(pos)
			, _texturePos(Point::Zero)
			, _frameCount(0)
		{

		}

	private:

		void update(GameManager & gameManager) override;

		void draw() const override;

	};
}