#pragma once


#include "../GameManager.h"


namespace Robot
{
	class AccessState : public GameState
	{
	private:

		int _framecount; // 経過フレーム数

		int _alpha;      // アルファ値

		int _stageId;    // ステージ番号

		std::unique_ptr<GameState> _nextState; // 次の状態

	public:

		AccessState(bool isTutorial);

	private:

		void update() override;

		void draw() const override;

	};
}