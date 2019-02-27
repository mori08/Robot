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
		
		std::unordered_map<String, ColorF>        _colorMap;      // �F�̃��X�g �{�^���̃L�[�ƌ��т���

		std::unordered_map<String, ProcessingPtr> _processingMap; // �{�^�����������Ƃ��̏������X�g

		String _selectedButtonKey; // �I������Ă���{�^���̃L�[

	public:

		/// <summary>
		/// �X�V
		/// </summary>
		virtual void update();

		/// <summary>
		/// �X�V(�I������Ă��Ȃ��E�B���h�E�̂Ƃ�)
		/// </summary>
		virtual void updateNonSelectedWindow();

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
		/// �{�^�����Ƃ炷����`�悵�܂��B
		/// </summary>
		void drawLight() const;

		/// <summary>
		/// �w�肳�ꂽ�L�[�����{�^�������邩�����܂��B
		/// </summary>
		/// <param name="buttonKey"> �{�^���̃L�[ </param>
		/// <returns> �L�[������Ƃ� true , �����łȂ��Ƃ� false </returns>
		/// <remarks>
		/// O(�{�^���̐�)�����̎��Ԃ�������܂�
		/// </remarks>
		bool keyExistsAtButtonList(const String & buttonKey) const;

		/// <summary>
		/// �w�肳�ꂽ���������邩�����܂��B
		/// </summary>
		/// <param name="buttonKey"> �{�^���̃L�[ </param>
		bool processingExists(const String & buttonKey) const
		{
			return _processingMap.find(buttonKey) != _processingMap.end();
		}

		/// <summary>
		/// �{�^���o�^�Ɋւ���A�̏������s���܂��B
		/// </summary>
		/// <param name="butttonKey"> �{�^���̃L�[ </param>
		/// <param name="region"> �͈� </param>
		void registerButton(const String & buttonKey, const Rect & region);

	private:

		/// <summary>
		/// �F��ύX���܂�
		/// </summary>
		/// <param name="color"> �ύX�������F </param>
		/// <param name="goalColor"> �ύX�� </param>
		static void changeColor(ColorF & color, const ColorF & goalColor);

	};
}
