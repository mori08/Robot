#pragma once

namespace Robot
{
	/*
	EventBase�N���X�̎����ł�EventManager�N���X�̎Q�Ƃ̂ݎg�p����
	EventManager�N���X�̎�����EventManager.h��EventManager.cpp�ōs��
	*/
	class EventManager;

	/*
	EventBase�N���X
	csv�t�@�C������C�x���g��ǂݍ��񂾂Ƃ�
	����1�s�������̃N���X�ɑΉ�����
	�C�x���g�̎�ނ��Ƃɂ��̃N���X�̔h���N���X���쐬����
	*/
	class EventBase
	{
	public:

		virtual void perform(EventManager & eventManager)const = 0;

	};
}

