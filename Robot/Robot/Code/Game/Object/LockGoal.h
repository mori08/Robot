#pragma once


#include "LockKey.h"


namespace Robot
{
	/*
	LockGoal�N���X
	�X�e�[�W�ɐݒu����錮��S�Ċl�����Ȃ���
	�S�[���ł��Ȃ�
	*/
	class LockGoal : public GameObject
	{
	private:

		using LockKeyList = std::vector<LockKey>;

	private:

		int   _frameCount; // �o�߃t���[����

		int   _lastKeyNum; // �J���Ă��Ȃ����̐�

		Point _texturePos; // �\������摜�̔ԍ�

		Vec2  _goal;       // �ړI�n

		LockKeyList _keyList; // ���̃��X�g

	public:

		/// <summary>
		/// �����S�[��
		/// </summary>
		/// <parma name="pos"> �������W </param>
		LockGoal(const Vec2 & pos);

	private:

		void update() override;

		void draw() const override;

		void drawLight() const override;

		/// <summary>
		/// LockKey���X�V����
		/// </summary>
		void updateKey();

	};
}