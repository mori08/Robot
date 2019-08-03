#pragma once


#include "ChangeTextureObject.h"


namespace Robot
{
	/*
	TelevisionObjectクラス
	背景で表示するテレビの表示内容
	*/
	class TelevisionObject : public EventObject
	{
	private:

		TextureRegion _texture; // 表示する画像

		bool          _on;      // テレビがついているとき true

	public:

		TelevisionObject(const Point & pos);

		void draw(const Vec2 & shakeSize) const override;

		/// <summary>
		/// テレビをつける
		/// </summary>
		void tvOn();

		

	};
}