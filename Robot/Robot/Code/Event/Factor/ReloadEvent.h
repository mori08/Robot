#pragma once


#include "../EventManager.h"


namespace Robot
{
	/*
	ReloadEvent�N���X
	LoadEventScene�ɑJ�ڂ���
	�����V�[����ǂݍ��݂Ȃ����܂�
	*/
	class ReloadEvent : public EventBase
	{
	private:

		bool load(const Info & info) override;

		void perform() const override;

		bool isCompleted() const override;

	};
}