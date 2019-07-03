#pragma once


#include "ChangeTextureObject.h"


namespace Robot
{
	/*
	HelpRobotObjectクラス
	イベントで使用するお手伝い型ロボットのオブジェクト
	*/
	class HelpRobotObject : public ChangeTextureObject
	{
	public:

		HelpRobotObject(const Point & pos);

	};
}