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

	public:

		/// <summary>
		/// ��ʂ̗h���ݒ肷��C�x���g
		/// </summary>
		/// <param name="arg"> �����̕�����̔z�� </param>
		ShakeEvent(const std::vector<String> & arg);

	private:

		void perform(EventManager & eventManager) const override;

		bool isCompleted(const EventManager & eventManager) const override;

	};
}