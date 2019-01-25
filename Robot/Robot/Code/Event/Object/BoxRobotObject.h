#pragma once


#include "EventObject.h"


namespace Robot
{
	/*
	BoxRobotObjectクラス
	イベントで使用する箱型ロボットのオブジェクト
	*/
	class BoxRobotObject : public EventObject
	{
	private:
		
		Size _textureSize;   // ロボット一台分の画像の大きさ
		String _textureName; // 画像の名前

	private:

		BoxRobotObject(const Point & pos);

		void draw(const Vec2 & shakeSize) const override;

	private:

		/// <summary>
		/// 縮小版の画像を使用します。
		/// </summary>
		void reduction();

		/// <summary>
		/// 拡大版の画像を使用します。
		/// </summary>
		void enlarged();

	};

}