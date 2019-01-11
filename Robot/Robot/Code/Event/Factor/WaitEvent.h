#pragma once


#include"../EventManager.h"


namespace Robot
{
	/*
	WaitEvent�N���X
	�w�肳�ꂽ�t���[�����܂őҋ@���܂�
	*/
	class WaitEvent : public EventBase
	{
	private:

		int _waitFrameCount;  // �ҋ@����t���[����

		int _beginFrameCount; // �ҋ@���J�n�����t���[����

	public:

		/// <summary>
		/// �ҋ@����C�x���g
		/// </summary>
		/// <param name="arg"> �����̕�����̔z�� </param>
		WaitEvent(const std::vector<String> & arg);

	private:

		void perform(EventManager & eventManager)const override;

		bool isCompleted(const EventManager & eventManager) const;

	};

}