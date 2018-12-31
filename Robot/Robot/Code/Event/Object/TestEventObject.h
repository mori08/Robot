#pragma once


#include"EventObject.h"


namespace Robot
{
	/*
	TestEventObjectクラス
	EventObjectクラスの挙動を確認する際使用します。
	*/
	class TestEventObject : public EventObject
	{
	private:

	public:

		TestEventObject(const Point & pos) : EventObject(pos)
		{
		}

		void draw() const override
		{
			Circle(_pos, 50).draw();
		}

	};
}