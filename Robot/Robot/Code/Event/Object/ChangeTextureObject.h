#pragma once


#include"EventObject.h"


namespace Robot
{
	/*
	ChangeTextureObjectクラス
	画像を随時変更するオブジェクトの基底クラス
	EventObjectの_noActを変更や
	_actMapへのchangeTextureActの登録によって
	画像を変更します
	*/
	class ChangeTextureObject : public EventObject
	{
	private:

		Point  _texturePos;  // 描画する画像の番号
		Size   _textureSize; // ロボット(など)一つ分の画像の大きさ
		String _textureName; // 画像の名前
		bool   _mirror;      // true のとき左右反転して描画

	public:

		/// <summary>
		/// 画像を変更するイベントオブジェクト
		/// </summary>
		/// <param name="pos"> 生成座標 </param>
		/// <param name="texturePos"> 描画する画像の番号 </param>
		/// <param name="textureSize"> 一つ分の画像の大きさ </param>
		/// <param name="textureName"> 画像の名前 </param>
		ChangeTextureObject(const Point & pos, const Point & texturePos, const Size & textureSize, const String & textureName);

	protected:

		virtual void  draw(const Vec2 & shakeSize) const;

		/// <summary>
		/// 描画する画像の番号を設定します。
		/// </summary>
		/// <param name="pos"> 座標 </param>
		void setTexturePos(const Point & pos)
		{
			_texturePos = pos;
			_act = noAct;
		}

		/// <summary>
		/// 表示する画像の名前を変更します。
		/// </summary>
		/// <param name="size"> 一つ分の画像の大きさ </param>
		/// <param name="name"> 画像の名前 </param>
		void changeTextureName(const Size & size, const String & name);

		void setTextureUpdating(const size_t & span, const std::vector<Point> & texturePosList);

		/// <summary>
		/// 画像を常に変更し続ける設定を行います。
		/// </summary>
		/// <param name="span"> 画像を切り替えるフレームの間隔 </param>
		/// <param name="texturePosList"> 画像の番号のリスト </param>
		void updateTexture(const size_t & span, const std::vector<Point> & texturePosList);

		/// <summary>
		/// 画像を切り替える演出を行います。
		/// </summary>
		/// <param name="span"> 画像を切り替えるフレームの間隔 </param>
		/// <param name="texturePosList"> 画像の番号のリスト </param>
		void changeTextureAct(const size_t & span, const std::vector<Point> & texturePosList);

	};
}