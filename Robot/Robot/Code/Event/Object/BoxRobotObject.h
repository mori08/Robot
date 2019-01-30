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
		
		Point  _texturePos;  // �`�悷��摜�̔ԍ�
		Size   _textureSize; // ���{�b�g��䕪�̉摜�̑傫��
		String _textureName; // �摜�̖��O

		int    _frameCount;  // �o�߃t���[����

	public:

		BoxRobotObject(const Point & pos);

	private:

		void draw(const Vec2 & shakeSize) const override;

		/// <summary>
		/// �k���ł̉摜���g�p���܂��B
		/// </summary>
		void reduction();

		/// <summary>
		/// �g��ł̉摜���g�p���܂��B
		/// </summary>
		void enlarged();

		/// <summary>
		/// �摜��؂�ւ��鉉�o���s���܂��B
		/// </summary>
		/// <param name="span"> �摜��؂�ւ���t���[���Ԋu </param>
		/// <param name="texturePosList"> �摜�̍��W�̃��X�g </param>
		void changeTextureAct(int span, const std::vector<Point> & texturePosList);

	};

}