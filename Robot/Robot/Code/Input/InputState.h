#pragma once


#include"Button.h"


namespace Robot
{
	/*
		���͂̏�Ԃ̊��
	*/
	class InputState
	{
	protected:

		using ButtonPtr = std::shared_ptr<Button>;

		using ButtonList = std::unordered_map<String, ButtonPtr>;

	public:

		/// <summary>
		/// ���肪���͂��ꂽ�������܂��B
		/// </summary>
		/// <returns> ���͂���Ă����� true , �����łȂ��Ƃ� false </returns>
		virtual bool decesion() const = 0;

		/// <summary>
		/// �I�v�V���������͂��ꂽ�������܂��B
		/// </summary>
		/// <returns> ���͂���Ă����Ƃ� true , �����łȂ��Ƃ� false </returns>
		virtual bool option() const = 0;

		/// <summary>
		/// ���͂��ꂽ�����������܂��B
		/// </summary>
		/// <returns> ���͂��ꂽ���� </returns>
		virtual Point direction() const = 0;

		/// <summary>
		/// �{�^����I�����܂��B
		/// </summary>
		/// <param name="selectedButton"> �I�𒆂̃{�^�� </param>
		/// <param name="buttonList"> �{�^���̃��X�g </param>
		/// <returns> 
		/// ���肪���͂��ꂽ�Ƃ��ɂ��̃{�^���̃L�[��Ԃ��܂��B
		/// �����I������Ă��Ȃ��Ƃ������l��Ԃ��܂��B
		/// </returns>
		/// <remarks>
		/// ���͂ɉ������{�^���I���̕ύX���s���܂��B
		/// 1�t���[����2�x�ȏ�g��Ȃ��ł��������B
		/// <remarks>
		virtual Optional<String> selectButton(ButtonPtr & selectedButton, const ButtonList & buttonList) const = 0;

	};
}