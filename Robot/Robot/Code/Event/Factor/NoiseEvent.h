#pragma once


#include "../EventManager.h"


namespace Robot
{
	/*
	NoiseEvent�N���X
	��ʂɃm�C�Y(�Q�[���I�[�o�[���o�̂悤�Ȃ���)��
	�w�肳�ꂽ���ԕ\������
	*/
	class NoiseEvent : public EventBase
	{
	private:

		bool _noise; // true �̂Ƃ� �m�C�Y�̕t�^

	private:

		bool load(const Info & info, const EventManager & eventManager)override;

		void perform(EventManager & eventManager) const override;

		bool isCompleted(const EventManager &) const override;

	};
}