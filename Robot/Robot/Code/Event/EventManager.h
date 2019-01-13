#pragma once

#include<Siv3D.hpp>

#include<queue>

#include"Object/EventObject.h"

#include"Factor/EventBase.h"

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

		using ObjectPtr  = std::shared_ptr<EventObject>;
		using ObjectList = std::map<String, ObjectPtr>;

		using EventPtr      = std::unique_ptr<EventBase>;
		using EventArg      = std::vector<String>;
		using MakeEventFunc = std::function<EventPtr(const EventArg &)>;
		using MakeEventMap  = std::unordered_map<String, MakeEventFunc>;

		using EventQueue = std::queue<EventPtr>;

	private:

		ObjectList   _objectList;     // EventOject�̃��X�g

		EventQueue   _eventQueue;     // EventBase�̔h�������o���L���[

		MakeEventMap _makeEventMap;   // �C�x���g�𐶐�����֐��̘A�z�z��

		String       _backgroundName; // �w�i�摜�̖��O

		int          _frameCount;     // �o�߃t���[����

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

		/// <summary>
		/// �S�ẴC�x���g���}�b�v�ɓo�^���܂��B
		/// </summary>
		void setAllEvent();

	private:

		/// <summary>
		/// �P�̃C�x���g���}�b�v�ɓo�^���܂��B
		/// </summary>
		/// <param name="name"> �C�x���g�� </param>
		template<typename eventType>
		void setEvent(const String & name)
		{
			_makeEventMap[name] = MakeEventFunc
			(
				[](const EventArg & eventArg)
				{
					return std::move(std::make_unique<eventType>(eventArg));
				}
			);
		}

		/// <summary>
		/// Event�̃t�@�C����ǂݍ��ݒ���_eventQueue���̑SEvent�����s���܂��B
		/// </summary>
		/// <remarks>
		/// �������p�ɍs���܂��B
		/// isCompleted�֐��ł̔���҂��͍s���܂���
		/// </remarks>
		void runAllEvent();

	public: // EventScene�Ŏg�p����֐�

		/// <summary>
		/// �C�x���g���L�q����csv�t�@�C����ǂݍ���
		/// </summary>
		/// <param name="eventName"> csv�t�@�C���̖��O </param>
		void load(const String & eventName);

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
		void generateObject(const String & name ,const std::shared_ptr<EventObject> & object)
		{
			_objectList[name] = object;
		}

		/// <summary>
		/// �w�i��ݒ肵�܂��B
		/// </summary>
		/// <param name="name"> �w�i�摜�̖��O </param>
		void setBackground(const String & name)
		{
			_backgroundName = name;
		}

		/// <summary>
		/// �o�߃t���[�������擾���܂��B
		/// </summary>
		int getFrameCount() const
		{
			return _frameCount;
		}

		/// <summary>
		/// �o�߃t���[������0�ɂ��܂��B
		/// </summary>
		void resetFrameCount()
		{
			_frameCount = 0;
		}

		/// <summary>
		/// �I�u�W�F�N�g�̃|�C���^���擾���܂��B
		/// </summary>
		/// <param name="name"> �I�u�W�F�N�g�̖��O </param>
		Optional<ObjectPtr> getObjectOpt(const String & name);

		/// <summary>
		/// �I�u�W�F�N�g���҂���Ԃ������܂��B
		/// </summary>
		/// <param name="name"> �I�u�W�F�N�g�̖��O </param>
		bool isWaitingObject(const String & name) const;

	};

}