#pragma once


#include "EventState.h"
#include <Siv3D.hpp>


namespace Robot
{
	/*
	PauseEventState�N���X
	�C�x���g���ꎞ���~���A
	������E�X�L�b�v����E���j���[
	��I������
	*/
	class PauseEventState : public EventState
	{
	private:

		RectF _cursor;

	public:

		PauseEventState();

		void update() override;

		void draw() const override;

	private:

		void drawButtonName(int y, const String & name) const;

	};
}