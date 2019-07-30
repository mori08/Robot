#pragma once


#include "PoliceEnemy.h"
#include "MonitorState\MonitorState.h"


namespace Robot
{
	/*
	PatrolTeamEnemyクラス
	PoliceEnemyを複数扱う
	ここで扱う光にPlayerが触れると
	PoliceEnemyが一気に追いかける
	*/
	class PatrolTeamEnemy : public GameObject
	{
	private:

		using MonitorState = std::unique_ptr<MonitorState>;

		using PoliceList   = std::vector<PoliceEnemy>;

	private:

		Vec2         _monitorPos;   // 監視の光の半径

		MonitorState _monitorState; // 監視の光の状態

		PoliceList   _policeList;   // PoliceEnemyの配列

	public:

		/// <summary>
		/// 監視チーム
		/// </summary>
		/// <parma name="pos"> 生成座標 </param>
		PatrolTeamEnemy(const Vec2 & pos);

		/// <summary>
		/// 監視用の光の状態を切り替える
		/// </summary>
		/// <param name="newState"> 新しい状態 </param>
		void changeMonitorState(MonitorState & newState)
		{
			_monitorState = std::move(newState);
		}

	private:

		void update(GameManager & gameManager) override;

		void draw() const override;

		void drawLight() const override;

	};
}