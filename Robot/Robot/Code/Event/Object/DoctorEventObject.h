#pragma once


#include "ChangeTextureObject.h"


namespace Robot
{
	/*
	DoctorEventObjectクラス
	ハカセの画像を表示
	*/
	class DoctorEventObject : public ChangeTextureObject
	{
	public:

		DoctorEventObject(const Point & pos)
			: ChangeTextureObject(pos, Point::Zero, Size(80, 100), L"Doctor")
		{
		}

	};
}