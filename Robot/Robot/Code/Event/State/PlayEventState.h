#pragma once

#include "EventState.h"


namespace Robot
{
	/*
	PlayEventState�N���X
	�C�x���g�����s���Ă�����
	*/
	class PlayEventState : public EventState
	{
	public:

		void update() override;

		void draw() const override;

	};
}