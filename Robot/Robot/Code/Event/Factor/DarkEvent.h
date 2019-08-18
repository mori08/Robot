#pragma once


#include "../EventManager.h"


namespace Robot
{
	/*
	DarkEvent�N���X
	�Ó]���܂��B
	*/
	class DarkEvent : public EventBase
	{
	private:

		int  _darkAlpha;   // �Ó]����Ƃ� 255 , ��������Ƃ� 0

	private:

		bool load(const Info & info) override;

		void perform() const override;

		bool isCompleted() const override;

	};
}