#pragma once


#include"../EventManager.h"


namespace Robot
{
	/*
	GenerateEvent�N���X
	EventObject�𐶐���
	EventManager��_objectList�ɒǉ����܂�
	Event��CSV�f�[�^�ł͕K��Run���O�ɋL�q����
	*/
	class GenerateEvent : public EventBase
	{
	private:

		using ObjectPtr    = std::shared_ptr<EventObject>;
		using GenerateFunc = std::function<ObjectPtr(const Point & pos)>;
		using FuncMap      = std::unordered_map<String, GenerateFunc>;

	private:

		static FuncMap generateObjMap;

	private:

		String _type; // ��������I�u�W�F�N�g�̎��

		String _name; // ���������I�u�W�F�N�g�̖��O

		Point  _pos;  // �I�u�W�F�N�g�𐶐�������W

	private:

		bool load(const Info & info) override;

		void perform() const override;

		bool isCompleted() const override;

	public:

		/// <summary>
		/// EventObject��o�^���܂��B
		/// </summary>
		static void setObjectMap();

	private:

		/// <summary>
		/// �^��eventObjectType��shared_ptr�����֐���Ԃ��܂��B
		/// </summary>
		/// <param name="name"> �I�u�W�F�N�g�̖��O </param>
		template<typename eventObjectType>
		static void makeGenerateFunc(const String & name)
		{
			generateObjMap[name] = GenerateFunc
			(
				[](const Point & pos) 
				{
					return std::make_shared<eventObjectType>(pos); 
				}
			);
		}

	};
}