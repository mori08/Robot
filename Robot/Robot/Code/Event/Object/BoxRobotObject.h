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
		
		Point  _texturePos;  // 描画する画像の番号
		Size   _textureSize; // ロボット一台分の画像の大きさ
		String _textureName; // 画像の名前

		int    _frameCount;  // 経過フレーム数

	public:

		BoxRobotObject(const Point & pos);

	private:

		void draw(const Vec2 & shakeSize) const override;

		/// <summary>
		/// 縮小版の画像を使用します。
		/// </summary>
		void reduction();

		/// <summary>
		/// 拡大版の画像を使用します。
		/// </summary>
		void enlarged();

		/// <summary>
		/// 画像を切り替える演出を行います。
		/// </summary>
		/// <param name="span"> 画像を切り替えるフレーム間隔 </param>
		/// <param name="texturePosList"> 画像の座標のリスト </param>
		void changeTextureAct(int span, const std::vector<Point> & texturePosList);

	};

}