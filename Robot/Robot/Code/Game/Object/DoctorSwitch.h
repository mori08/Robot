#pragma once


#include "../GameManager.h"


namespace Robot
{
	/*
	DoctorSwitchクラス
	DoctorEnemyで保持する
	プレイヤーが近づくとフラグが切り替わる
	*/
	class DoctorSwitch : public GameObject
	{
	protected:

		bool  _isPressed;  // 初期値 false プレイヤーが近づくと true に切り替わる

	private:

		int   _frameCount; // 経過フレーム数

		Point _texturePos; // 表示する画像の番号

	public:

		DoctorSwitch(const Vec2 & pos);

		void update(GameManager & gameManager) override;

		void draw() const override;

		void drawLight() const override;

		/// <summary>
		/// プレイヤーが近づき_isPressedがtrueになったとき true を返す
		/// </summary>
		/// <returns> 
		/// _isPressedが true になったら true
		/// 既に true のとき または false のとき false
		/// </returns>
		bool checkPlayer(const GameManager & gameManager);

	protected:

		/// <summary>
		/// 移動ベクトルを取得します。
		/// </summary>
		/// <param name="gameManager"> GameManagerクラスのインスタンス </param>
		virtual Vec2 getMoveVec(GameManager &)
		{
			return Vec2::Zero;
		}

	};
}