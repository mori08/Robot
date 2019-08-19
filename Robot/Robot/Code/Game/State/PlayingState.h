#pragma once


#include "../GameManager.h"


namespace Robot
{
	/*
	PlayingStateクラス
	ゲームプレイ中のGameManagerの状態
	*/
	class PlayingState : public GameState
	{
	private:

		void update() override;

		void draw() const override;

	};
}