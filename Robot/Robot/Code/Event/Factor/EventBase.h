#pragma once


#include <Siv3D.hpp>


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

	���̃N���X�̔h���N���X�����Ƃ���
	EventManager��setAllEvent�֐��ɓo�^����
	*/
	class EventBase
	{
	protected:

		using Info = std::vector<String>;

	protected:

		bool _isSuccess;

	public:

		EventBase();

		/// <summary>
		/// ������̔z����󂯎��A�C�x���g�̏ڍׂ����肵�܂��B
		/// </summary>
		/// <param name="info"> �C�x���g�̏ڍ� </param>
		/// <returns> ����������ł����Ƃ� true , �����łȂ��Ƃ� false </returns>
		virtual bool load(const Info & info) = 0;

		/// <summary>
		/// Event�����������[�h�ł��Ă��邩�m�F���A���s���܂��B
		/// </summary>
		void checkAndPerform() const;

		/// <summary>
		/// �I�����Ă��邩�����܂��B
		/// </summary>
		/// <returns> �I�����Ă���Ƃ� true , �����łȂ��Ƃ� false </returns>
		virtual bool isCompleted() const = 0;

	protected:

		/// <summary>
		/// Event�����s���܂��B
		/// </summary>
		virtual void perform() const = 0;

	};
}

