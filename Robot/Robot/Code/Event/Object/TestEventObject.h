#pragma once


#include"EventObject.h"


namespace
{
	const int WHITE = 240;
	const int BLACK = 15;

	const int RADIAN_BASE = 50;
	const int SHAKE_WIDTH = 30;

	const int ACT_FRAME_COUNT = 60;
}


namespace Robot
{
	/*
	TestEventObjectクラス
	EventObjectクラスの挙動を確認する際使用します。
	*/
	class TestEventObject : public EventObject
	{
	private:

		Color color;

		int radian;

	public:

		TestEventObject(const Point & pos) 
			: EventObject(pos)
			, color(Color(WHITE))
			, radian(RADIAN_BASE)
		{
			_actMap[L"Black"] = std::make_shared<Act>([this]() { changeBlack(); });
			_actMap[L"White"] = std::make_shared<Act>([this]() { changeWhite(); });
			_actMap[L"Shake"] = std::make_shared<Act>([this]() { shake(); });
		}

		void draw(const Vec2 & shakeSize) const override
		{
			Circle(_pos + shakeSize, radian).draw(color);
		}

	private:

		void changeBlack()
		{
			color = Color(BLACK);
			finishAct();
		}

		void changeWhite()
		{
			color = Color(WHITE);
			finishAct();
		}

		void shake()
		{
			radian = RADIAN_BASE + Random(SHAKE_WIDTH);
			
			if (_actFrameCount > ACT_FRAME_COUNT)
			{
				radian = RADIAN_BASE;
				finishAct();
			}
		}

	};
}