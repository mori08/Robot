#pragma once


#include "ChangeTextureObject.h"


namespace Robot
{
	/*
	BoxRobotObjectクラス
	イベントで使用する箱型ロボットのオブジェクト
	*/
	class BoxRobotObject : public ChangeTextureObject
	{
	public:

		BoxRobotObject(const Point & pos);

	};

}