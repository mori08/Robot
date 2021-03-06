#pragma once


#include "DoctorDefence.h"
#include "DoctorSwitch.h"


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

		using SwitchList  = std::vector<DoctorSwitch>;

		using EnemyList   = std::vector<std::unique_ptr<GameObject>>;

	private:

		double      _defenceRadian; // DoctorDefenceの回転の角度

		DefenceList _defenceList;   // DoctorDefenceのリスト

		SwitchList  _switchList;    // DoctorSwitchのリスト

		EnemyList   _enemyList;     // スイッチが押されたときに呼び出したオブジェクト

		int   _frameCount; // 経過フレーム数

		Point _texturePos; // 表示する画像の番号

	public:

		DoctorEnemy(const Vec2 & pos);

		void update() override;

		void draw() const override;

		void drawLight() const override;

	private:

		/// <summary>
		/// DoctorDefenceの目的地指定と更新
		/// </summary>
		void updateDefence();

		/// <summary>
		/// DoctorSwitchの判定と更新
		/// </summary>
		void updateSwitch();

	};
}