#pragma once


#include "ChangeTextureObject.h"


namespace Robot
{
	/*
	AccompanyObjectクラス
	Accompany.pngを表示
	*/
	class AccompanyObject : public ChangeTextureObject
	{
	public:

		AccompanyObject(const Point & pos);

	};

}