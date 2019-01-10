#pragma once


#include"../EventManager.h"


namespace Robot
{
	/*
	BackgoundEvent�N���X
	EventScene�̔w�i��ϊ����܂�
	*/
	class BackgroundEvent : public EventBase
	{
	private:

		String _name; // �w�i�摜�̖��O

	public:

		/// <summary>
		/// �w�i�𐶐�����C�x���g�𐶐����܂��B
		/// </summary>
		/// <param name="arg"> �����̕�����̔z�� </param>
		BackgroundEvent(const std::vector<String> & arg);

	private:

		void perform(EventManager & eventManager) const override;

		bool isCompleted(const EventManager &) const override;

	};

}