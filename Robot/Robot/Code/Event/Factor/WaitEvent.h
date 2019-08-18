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

	private:

		bool load(const Info & info) override;

		void perform() const override;

		bool isCompleted() const override;

	};

}