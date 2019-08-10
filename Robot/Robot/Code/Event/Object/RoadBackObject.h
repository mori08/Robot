#pragma once

#include "EventObject.h"

namespace Robot
{
	/*
	RoadBackObject�N���X
	�X�N���[�������铹��\��������
	Act�C�x���g�œ�����\�������A�X�N���[�����~�߂�
	*/
	class RoadBackObject : public EventObject
	{
	private:

		using TextureSet = std::pair<TextureRegion, TextureRegion>;

	private:

		int        _scrollPx; // �摜�����炷x���W

		TextureSet _texture;  // �\������摜

	public:

		RoadBackObject(const Point & pos);

		void draw(const Vec2 & shakeSize) const override;

	public:

		void scroll();

		void goEntrance();

		void stopEntrance();

	};
}