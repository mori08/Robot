#pragma once


#include "../GameManager.h"


namespace Robot
{
	/*
	DoctorSwitch�N���X
	DoctorEnemy�ŕێ�����
	�v���C���[���߂Â��ƃt���O���؂�ւ��
	*/
	class DoctorSwitch : public GameObject
	{
	protected:

		bool  _isPressed;  // �����l false �v���C���[���߂Â��� true �ɐ؂�ւ��

	private:

		int   _frameCount; // �o�߃t���[����

		Point _texturePos; // �\������摜�̔ԍ�

	public:

		DoctorSwitch(const Vec2 & pos);

		void update() override;

		void draw() const override;

		void drawLight() const override;

		/// <summary>
		/// �v���C���[���߂Â�_isPressed��true�ɂȂ����Ƃ� true ��Ԃ�
		/// </summary>
		/// <returns> 
		/// _isPressed�� true �ɂȂ����� true
		/// ���� true �̂Ƃ� �܂��� false �̂Ƃ� false
		/// </returns>
		bool checkPlayer();

	protected:

		/// <summary>
		/// �ړ��x�N�g�����擾���܂��B
		/// </summary>
		virtual Vec2 getMoveVec()
		{
			return Vec2::Zero;
		}

	};
}