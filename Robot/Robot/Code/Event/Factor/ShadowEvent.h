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

		bool load(const Info & info) override;

		void perform() const override;

		bool isCompleted() const override;

	};
}