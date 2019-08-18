#pragma once


#include "../EventManager.h"


namespace Robot
{
	/*
	ShakeEvent�N���X
	EventManager��setShake�֐���p����
	��ʂ̗h���ݒ肵�܂�
	*/
	class ShakeEvent : public EventBase
	{
	private:

		double _size; // �h��̑傫��

		int    _span; // �h��̒���(�t���[����)

	private:

		bool load(const Info & info) override;

		void perform() const override;

		bool isCompleted() const override;

	};
}