#pragma once

#include<Siv3D.hpp>

namespace Robot
{
	/*
	EventManager�N���X
	CSV�t�@�C������Event��ǂݍ���
	EventObject�̊Ǘ�
	�w�i����ʁC���o�̐ݒ�
	*/
	class EventManager
	{
	private:

		int _eventNumber;

	private:

		EventManager();

		EventManager(const EventManager&)            = default;
		EventManager& operator=(const EventManager&) = default;
		EventManager(EventManager&&)                 = default;
		EventManager& operator=(EventManager&&)      = default;

	public:

		/// <summary>
		/// �V���O���g���Ƃ��ĊǗ����Ă���EventManager�̃C���X�^���X���擾���܂��B
		/// </summary>
		/// <returns> �C���X�^���X </returns>
		static EventManager & Instance()
		{
			static EventManager eventManager;
			return eventManager;
		}

	};

}