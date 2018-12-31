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
	protected:

		bool _isSuccess;

	public:

		EventBase();

		/// <summary>
		/// Event�����������[�h�ł��Ă��邩�m�F���A���s���܂��B
		/// </summary>
		/// <param name="eventManager"> EventManager </param>
		void checkAndPerform(EventManager & eventManager) const;

		/// <summary>
		/// �I�����Ă��邩�����܂��B
		/// </summary>
		/// <param name="eventManager"> EventManager </param>
		/// <returns> �I�����Ă���Ƃ� true , �����łȂ��Ƃ� false </returns>
		virtual bool isCompleted(const EventManager & eventManager) const = 0;

	protected:

		/// <summary>
		/// Event�����s���܂��B
		/// </summary>
		/// <param name="eventManager"> EventManager </param>
		virtual void perform(EventManager & eventManager) const = 0;

	};
}

