#pragma once


#include"../Main.h"
#include"Light.h"


namespace Robot
{

	class TitleScene : public MyApp::Scene
	{
	private:

		int              _generateLightFrameCount; // ���𐶐�����܂ł̃t���[����
		std::list<Light> _lightList;               // ���̃��X�g

		RectF            _cursor;                  // �w�肵���{�^���͈̔�

	public:

		TitleScene();

		void init() override;

		void update() override;

		void draw()const override;

	};

}