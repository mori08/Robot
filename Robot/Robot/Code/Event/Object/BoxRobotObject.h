#pragma once


#include "EventObject.h"


namespace Robot
{
	/*
	BoxRobotObject�N���X
	�C�x���g�Ŏg�p���锠�^���{�b�g�̃I�u�W�F�N�g
	*/
	class BoxRobotObject : public EventObject
	{
	private:
		
		Size _textureSize;   // ���{�b�g��䕪�̉摜�̑傫��
		String _textureName; // �摜�̖��O

	private:

		BoxRobotObject(const Point & pos);

		void draw(const Vec2 & shakeSize) const override;

	private:

		/// <summary>
		/// �k���ł̉摜���g�p���܂��B
		/// </summary>
		void reduction();

		/// <summary>
		/// �g��ł̉摜���g�p���܂��B
		/// </summary>
		void enlarged();

	};

}