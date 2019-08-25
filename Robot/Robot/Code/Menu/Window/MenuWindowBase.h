#pragma once


#include<Siv3D.hpp>
#include"State/WindowState.h"
#include"../../Input/Button.h"


namespace Robot
{
	class MenuScene;

	/*
	MenuWindowBase�N���X
	MenuScene�ɕ\������Windowwo��\��
	*/
	class MenuWindowBase
	{
	protected:

		using Processing    = std::function<void()>;
		using ProcessingPtr = std::unique_ptr<std::function<void()>>;

	public:

		static const ColorF NON_SHOWED_COLOR;
		static const ColorF SHOWED_COLOR;
		static const ColorF NON_SELECTED_COLOR;
		static const ColorF SELECTED_COLOR;

	protected:

		std::unique_ptr<WindowState>              _state;         // ���

		std::vector<std::shared_ptr<Button>>      _buttonPtrList; // �{�^���̃|�C���^�̃��X�g
		
		std::unordered_map<String, String>        _buttonNameMap; // �{�^���ɕ\�����閼�O�̃}�b�v

		std::unordered_map<String, ProcessingPtr> _processingMap; // �{�^�����������Ƃ��̏������X�g

		ColorF        _white;             // ���F

		ColorF        _boardColor;        // �{�[�h�̐F

		RectF         _cursor;            // �J�[�\��

		ProcessingPtr _closedProcessing;  // �E�B���h�E�����Ƃ��̏���

		String        _selectedButtonKey; // �I������Ă���{�^���̃L�[

		Vec2          _openOffset;        // �E�B���h�E���J���Ƃ��̉��o�J�n�ʒu

	public: // MenuScene�Ŏg�p

		MenuWindowBase();

		/// <summary>
		/// �X�V
		/// </summary>
		virtual void update();

		/// <summary>
		/// �`��
		/// </summary>
		virtual void draw() const;

		/// <summary>
		/// �E�B���h�E���J���܂��B
		/// </summary>
		void open();

		/// <summary>
		/// �E�B���h�E��I�����܂��B
		/// </summary>
		void select();

		/// <summary>
		/// �E�B���h�E�̑I�����O���܂��B
		/// </summary>
		void nonSelect();

		/// <summary>
		/// �E�B���h�E����܂��B
		/// </summary>
		void close();

		/// <summary>
		/// InputManager�Ƀ{�^���̏����X�V���܂��B
		/// </summary>
		virtual void updateInputManager() const = 0;

		/// <summary>
		/// �E�B���h�E������Ƃ��̏�����ݒ肵�܂��B
		/// </summary>
		void setClosedProcessing(ProcessingPtr processing)
		{
			_closedProcessing = std::move(processing);
		}

	public: // WindowState�Ŏg�p

		/// <summary>
		/// �{�^���̐F��ύX���܂��B
		/// </summary>
		/// <param name="color"> �F </param>
		void setColor(const ColorF & color);

		/// <summary>
		/// �{�[�h�̃A���t�@�l��ύX���܂��B
		/// </summary>
		/// <param name="alpha"> �A���t�@�l </param>
		void setBoardAlpha(double alpha);

		/// <summary>
		/// �{�^���̐����擾���܂�
		/// </summary>
		int numOfButton() const
		{
			return (int)_buttonPtrList.size();
		}

		/// <summary>
		/// �I�𒆂̍X�V
		/// </summary>
		void updateSelectedWindowButton();

		/// <summary>
		/// �{�^���ƌ���`�悵�܂��B
		/// </summary>
		/// <param name="offsetList"> ���炵 </param>
		void drawButtonAndLight(const Vec2 & offset = Vec2::Zero) const;

		/// <summary>
		/// ��Ԃ�ύX���܂��B
		/// </summary>
		void changeState(std::unique_ptr<WindowState> state)
		{
			_state = std::move(state);
		}

	protected:

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
		/// <param name="processing"> �{�^�����������Ƃ��̏��� </param>
		void registerButton(const String & buttonKey, const Rect & region, ProcessingPtr processing);

		/// <summary>
		/// �{�^���ɕ\�����閼�O��ݒ肵�܂��B
		/// </summary>
		/// <param name="buttonKey"> �{�^���̃L�[ </param>
		/// <param name="buttonName"> �{�^���̖��O </param>
		void setButtonName(const String & buttonKey, const String & buttonName)
		{
			_buttonNameMap[buttonKey] = buttonName;
		}

	private:

		/// <summary>
		/// �F��ύX���܂�
		/// </summary>
		/// <param name="color"> �ύX�������F </param>
		/// <param name="goalColor"> �ύX�� </param>
		static void changeColor(ColorF & color, const ColorF & goalColor);

	};
}
