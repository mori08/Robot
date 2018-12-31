#pragma once


#include"EventObject.h"


namespace Robot
{
	/*
	TestEventObject�N���X
	EventObject�N���X�̋������m�F����ێg�p���܂��B
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