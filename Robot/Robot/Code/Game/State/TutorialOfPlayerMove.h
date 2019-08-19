#pragma once


#include "../GameManager.h"


namespace Robot
{
	/*
	TutorialOfPlayerMoveクラス
	プレイヤーの動作のチュートリアル
	*/
	class TutorialOfPlayerMove : public GameState
	{
	private:

		Vec2   _prePlayerPos;   // 1フレーム前のプレイヤーの座標
		double _playerMoveDist; // プレイヤーの移動距離
		size_t _frameCount;     // 経過フレーム数

	public:

		TutorialOfPlayerMove();

	private:

		void update() override;

		void draw() const override;

	};
}