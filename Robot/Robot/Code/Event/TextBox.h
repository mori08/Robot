#pragma once


#include<Siv3D.hpp>


namespace Robot
{
	/*
	TextBox�N���X
	�C�x���g�Ńe�L�X�g�{�b�N�X�̍X�V�E�`����s���܂��B
	*/
	class TextBox
	{
	private:
		
		size_t _drawTextLength; // �`�悷��e�L�X�g�̒���

		String _text;           // �\������e�L�X�g

		String _speakerName;    // �b����̖��O

		String _iconName;       // �\������A�C�R���̖��O

	public:

		TextBox()
			: _drawTextLength(0)
		{
		}

		/// <summary>
		/// �\������e�L�X�g�Ȃǂ̐ݒ�
		/// </summary>
		/// <param name="text"> �\������e�L�X�g </param>
		/// <param name="speakerName"> �b����̖��O </param>
		/// <param name="iconName"> �\������A�C�R���̖��O </param>
		void set(const String & text, const String & speakerName, const String & iconName);

		/// <summary>
		/// ������
		/// </summary>
		void reset();

		/// <summary>
		/// �X�V
		/// </summary>
		void update();

		/// <summary>
		/// �`��
		/// </summary>
		void draw()const;

		/// <summary>
		/// �e�L�X�g�Ȃǂ�ݒ�ł��邩�����܂�
		/// </summary>
		/// <returns> �ݒ�ł���Ƃ� true , �����łȂ��Ƃ� false </returns>
		bool isReady() const
		{
			_drawTextLength >= _text.length;
		}

	};
}