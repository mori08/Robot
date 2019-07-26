#pragma once


#include "DoctorDefence.h"


namespace Robot
{
	/*
	DoctorEnemyクラス
	ゴールと敵を複数もつ
	プレイヤーが指定の座標に来た時的を入れ替える処理をする
	*/
	class DoctorEnemy : public GameObject
	{
	private:

		using DefenceList = std::list<std::unique_ptr<DoctorDefence>>;

	private:

		double      _defenceRadian; // DoctorDefenceの回転の角度

		DefenceList _defenceList;   // DoctorDefenceのリスト

		int   _frameCount; // 経過フレーム数

		Point _texturePos; // 表示する画像の番号

	public:

		DoctorEnemy(const Vec2 & pos);

		void update(GameManager & gameManager) override;

		void draw() const override;

	private:

		/// <summary>
		/// DoctorDefenceの目的地指定と更新
		/// </summary>
		/// <param name="gameManager"> GameManagerのインスタンス </param>
		void updateDefence(GameManager & gameManager);

	};
}