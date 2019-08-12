#pragma once


#include "ChangeTextureObject.h"


namespace Robot
{
	/*
	DoctorEventObject�N���X
	�n�J�Z�̉摜��\��
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