#pragma once


#include<Siv3D.hpp>
#include"State/WindowState.h"
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

	public:

		static const ColorF NON_SHOWED_COLOR;
		static const ColorF NON_SELECTED_COLOR;
		static const ColorF SELECTED_COLOR;

	protected:

		std::unique_ptr<WindowState>              _state;         // ���

		std::vector<std::shared_ptr<Button>>      _buttonPtrList; // �{�^���̃|�C���^�̃��X�g
		
		std::unordered_map<String, ColorF>        _colorMap;      // �F�̃��X�g �{�^���̃L�[�ƌ��т���

		std::unordered_map<String, ProcessingPtr> _processingMap; // �{�^�����������Ƃ��̏������X�g

		String _selectedButtonKey; // �I������Ă���{�^���̃L�[

		Vec2   _openOffset;        // �E�B���h�E���J���Ƃ��̉��o�J�n�ʒu

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
		/// �{�^�����������Ƃ��̏�����ݒ肵�܂��B
		/// </summary>
		/// <param name="buttonKey"> �{�^���̃L�[ </param>
		/// <param name="processing"> �{�^�����������Ƃ��̏��� </param>
		void setClickedProcessing(const String & buttonKey, ProcessingPtr processing);
		
	public: // WindowState�Ŏg�p

		/// <summary>
		/// �{�^���̐F��ύX���܂��B
		/// </summary>
		/// <param name="color"> �F </param>
		/// <param name="num"> �ύX����� </param>
		void setColor(const Color color, size_t num = String::npos);

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
		void drawButtonAndLight(const std::vector<Vec2> & offsetList = std::vector<Vec2>(), const std::vector<double> & alphaList = std::vector<double>()) const;

		/// <summary>
		/// ��Ԃ�ύX���܂��B
		/// </summary>
		void changeState(std::unique_ptr<WindowState> state)
		{
			_state = std::move(state);
		}

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
