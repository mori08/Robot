#pragma once


#include "ChangeTextureObject.h"


namespace Robot
{
	/*
	TelevisionObject�N���X
	�w�i�ŕ\������e���r�̕\�����e
	*/
	class TelevisionObject : public EventObject
	{
	private:

		TextureRegion _texture; // �\������摜

		bool          _on;      // �e���r�����Ă���Ƃ� true

	public:

		TelevisionObject(const Point & pos);

		void draw(const Vec2 & shakeSize) const override;

		/// <summary>
		/// �e���r������
		/// </summary>
		void tvOn();

		

	};
}