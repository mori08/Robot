#pragma once


#include"EventObject.h"


namespace Robot
{
	/*
	ChangeTextureObject�N���X
	�摜�𐏎��ύX����I�u�W�F�N�g�̊��N���X
	EventObject��_noAct��ύX��
	_actMap�ւ�changeTextureAct�̓o�^�ɂ����
	�摜��ύX���܂�
	*/
	class ChangeTextureObject : public EventObject
	{
	private:

		Point  _texturePos;  // �`�悷��摜�̔ԍ�
		Size   _textureSize; // ���{�b�g(�Ȃ�)����̉摜�̑傫��
		String _textureName; // �摜�̖��O

	public:

		/// <summary>
		/// �摜��ύX����C�x���g�I�u�W�F�N�g
		/// </summary>
		/// <param name="pos"> �������W </param>
		/// <param name="texturePos"> �`�悷��摜�̔ԍ� </param>
		/// <param name="textureSize"> ����̉摜�̑傫�� </param>
		/// <param name="textureName"> �摜�̖��O </param>
		ChangeTextureObject(const Point & pos, const Point & texturePos, const Size & textureSize, const String & textureName);

	protected:

		virtual void  draw(const Vec2 & shakeSize) const;

		/// <summary>
		/// �\������摜�̖��O��ύX���܂��B
		/// </summary>
		/// <param name="name"> �摜�̖��O </param>
		/// <param name="size"> ����̉摜�̑傫�� </param>
		void changeTextureName(const String & name, const Size & size);

		/// <summary>
		/// �摜����ɕύX��������ݒ���s���܂��B
		/// </summary>
		/// <param name="span"> �摜��؂�ւ���t���[���̊Ԋu </param>
		/// <param name="texturePosList"> �摜�̔ԍ��̃��X�g </param>
		void setUpdateTexture(size_t span, const std::vector<Point> & texturePosList);

		/// <summary>
		/// �摜��؂�ւ��鉉�o���s���܂��B
		/// </summary>
		/// <param name="span"> �摜��؂�ւ���t���[���̊Ԋu </param>
		/// <param name="texturePosList"> �摜�̔ԍ��̃��X�g </param>
		void changeTextureAct(size_t, const std::vector<Point> & texturePosList);



	};
}