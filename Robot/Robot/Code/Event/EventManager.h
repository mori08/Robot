#pragma once

#include<Siv3D.hpp>

#include<queue>

#include"EventObject.h"

#include"EventBase.h"

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

		using ObjectList = std::map<String, EventObject>;

		using EventQueue = std::queue<std::shared_ptr<EventBase>>;

	private:

		ObjectList _objectList; // EventOject�̃��X�g

		EventQueue _eventQueue; // EventBase�̔h�������o���L���[

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

	public: // EventScene�Ŏg�p����֐�

		/// <summary>
		/// �X�V
		/// </summary>
		void update();

		/// <summary>
		/// �`��
		/// </summary>
		void draw() const;

	public: // EventBase�̔h���N���X�Ŏg�p����֐�

		/// <summary>
		/// EventObject��ǉ����܂��B
		/// </summary>
		/// <param name="name"> ���O </param>
		/// <param name="object"> �I�u�W�F�N�g </param>
		void generateObject(const String & name ,const std::shared_ptr<EventObject> & object);

	};

}