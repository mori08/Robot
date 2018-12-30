#pragma once


#include"EventManager.h"


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
		using GenerateFunc = std::function<ObjectPtr()>;
		using FuncMap      = std::unordered_map<String, GenerateFunc>;

	private:

		static FuncMap objectMap;

	private:

		String _type; // 生成するオブジェクトの種類

		String _name; // 生成したオブジェクトの名前

		Point  _pos;  // オブジェクトを生成する座標

	public:

		/// <summary>
		/// オブジェクトを生成するイベントを生成します。
		/// </summary>
		/// <param name="type"> 種類 </param>
		/// <param name="name"> 名前 </param>
		/// <param name="x"> x座標 </param>
		/// <param name="y"> y座標 </param>
		GenerateEvent(const String & type, const String & name, const String & x, const String & y);

		void perform(EventManager & eventManager)const override;

	public:

		static void setObjectMap();

	};
}