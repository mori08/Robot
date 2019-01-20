#pragma once


#include "../EventManager.h"


namespace Robot
{
	/*
	TextEvent�N���X
	TextBox�̊֐����g�p���A
	�e�L�X�g�̕\�����s���B
	*/
	class TextEvent : public EventBase
	{
	private:

		String _speakerName; // �b����̖��O

		String _iconName;    // �A�C�R���̉摜�̖��O

		String _text;        // �\������e�L�X�g

	private:

		bool load(const Info & info, const EventManager &) override;

		void perform(EventManager & eventManager) const override;

		bool isCompleted(const EventManager & eventManager) const override;

	};
}