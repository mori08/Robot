#pragma once


#include"EventManager.h"


namespace Robot
{
	/*
	GenerateEvent�N���X
	EventObject�𐶐���
	EventManager��_objectList�ɒǉ����܂�
	*/
	class GenerateEvent : public EventBase
	{
	private:

		using ObjectPtr    = std::shared_ptr<EventObject>;
		using GenerateFunc = std::function<ObjectPtr()>;
		using FuncMap      = std::unordered_map<String, GenerateFunc>;

	private:

		static FuncMap objectMap;

	private:

		String _type; // ��������I�u�W�F�N�g�̎��

		String _name; // ���������I�u�W�F�N�g�̖��O

		Point  _pos;  // �I�u�W�F�N�g�𐶐�������W

	public:

		/// <summary>
		/// �I�u�W�F�N�g�𐶐�����C�x���g�𐶐����܂��B
		/// </summary>
		/// <param name="type"> ��� </param>
		/// <param name="name"> ���O </param>
		/// <param name="x"> x���W </param>
		/// <param name="y"> y���W </param>
		GenerateEvent(const String & type, const String & name, const String & x, const String & y);

		void perform(EventManager & eventManager)const override;

	public:

		static void setObjectMap();

	};
}