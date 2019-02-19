#pragma once


#include<Siv3D.hpp>
#include"../../Input/Button.h"


namespace Robot
{
	/*
	MenuWindowBase�N���X
	MenuScene�ɕ\������Windowwo��\��
	*/
	class MenuWindowBase
	{
	private:

		using ProcessingPtr = std::unique_ptr<std::function<void()>>;

	protected:

		std::vector<std::shared_ptr<Button>>      _buttonPtrList; // �{�^���̃|�C���^�̃��X�g
		
		std::unordered_map<String, Color>         _colorMap;      // �F�̃��X�g �{�^���̃L�[�ƌ��т���

		std::unordered_map<String, ProcessingPtr> _processingMap; // �{�^�����������Ƃ��̏������X�g

	public:

		/// <summary>
		/// �X�V
		/// </summary>
		virtual void update() = 0;

		/// <summary>
		/// �`��
		/// </summary>
		virtual void draw() const = 0 ;

		/// <summary>
		/// InputManager�Ƀ{�^���̏����X�V���܂��B
		/// </summary>
		virtual void updateInputManager() const = 0;

		/// <summary>
		/// �{�^�����������Ƃ��̏�����ݒ肵�܂��B
		/// </summary>
		/// <param name="buttonKey"> �{�^���̃L�[ </param>
		/// <param name="processing"> �{�^�����������Ƃ��̏��� </param>
		void setClickedProcessing(const String & buttonKey, ProcessingPtr processing);
		
	protected:

		/// <summary>
		/// �w�肳�ꂽ�L�[�����{�^�������邩�����܂��B
		/// </summary>
		/// <param name="buttonKey"> �{�^���̃L�[ </param>
		/// <returns> �L�[������Ƃ� true , �����łȂ��Ƃ� false </returns>
		/// <remarks>
		/// O(�{�^���̐�)�����̎��Ԃ�������܂�
		/// </remarks>
		bool keyExistsAtButtonList(const String & buttonKey) const;

	};
}
