#pragma once


#include"../EventManager.h"


namespace Robot
{
	/*
	InitEvent�N���X
	��̃C�x���g
	�L���[�̍ŏ��ɓ���Ă���
	*/
	class InitEvent : public EventBase
	{
	public:

		InitEvent()
		{
			_isSuccess = true;
		}

	private:

		bool load(const Info &, const EventManager &) override
		{
			return true;
		}

		void perform(EventManager &)const override
		{
		}

		bool isCompleted(const EventManager &)const override
		{
			return true;
		}

	};

}
