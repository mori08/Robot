#pragma once


#include <Siv3D.hpp>


namespace Robot
{
	class PatrolTeamEnemy;

	/*
	MonitorStateクラス
	PatrolTeamEnemyでの監視用の光の動きを制御する
	*/
	class MonitorState
	{
	protected:

		const double RADIUS        = 40;          // 光の半径
		const double CHASE_DISTANCE = RADIUS + 20; // 追いかけ始まる距離

	public:

		/// <summary>
		/// 移動先の指定
		/// </summary>
		/// <param name="monitorPos"> 監視用の光の座標 </param>
		virtual void getMoveVec(Vec2 & monitorPos) = 0;

		/// <summary>
		/// 監視用の光の描画
		/// </summary>
		/// <param name="monitorPos"> 監視用の光の座標 </param>
		void drawLight(const Vec2 & monitorPos) const;

		/// <summary>
		/// 条件に応じた状態遷移を行う
		/// </summary>
		virtual void changeState(PatrolTeamEnemy & patrolTeam) = 0;

	};
}