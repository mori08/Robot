#pragma once


#include "../EventManager.h"


namespace Robot
{
	/*
	ShadowEvent�N���X
	�e�̌��ʂ�t�^���܂��B
	*/
	class ShadowEvent : public EventBase
	{
	private:

		bool _shadow; // �e��t�^����Ƃ� true , �����łȂ��Ƃ� false

	private:

		bool load(const Info & info, const EventManager &) override;

		void perform(EventManager & eventManager) const override;

		bool isCompleted(const EventManager &) const override;

	};
}