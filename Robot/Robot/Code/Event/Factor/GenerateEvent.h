#pragma once


#include"../EventManager.h"


namespace Robot
{
	/*
	GenerateEventクラス
	EventObjectを生成し
	EventManagerの_objectListに追加します
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

		String _type; // 生成するオブジェクトの種類

		String _name; // 生成したオブジェクトの名前

		Point  _pos;  // オブジェクトを生成する座標

	public:

		/// <summary>
		/// オブジェクトを生成するイベントを生成します。
		/// </summary>
		/// <param name="arg"> 引数の文字列の配列 </param>
		GenerateEvent(const std::vector<String> & arg);

	private:

		void perform(EventManager & eventManager)const override;

		bool isCompleted(const EventManager &) const override;

	public:

		/// <summary>
		/// EventObjectを登録します。
		/// </summary>
		static void setObjectMap();

	private:

		/// <summary>
		/// 型名eventObjectTypeのshared_ptrを作る関数を返します。
		/// </summary>
		/// <param name="name"> オブジェクトの名前 </param>
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