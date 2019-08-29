#pragma once


#include"../MyLibrary.h"
#include"TitleLight.h"


namespace Robot
{

	class TitleScene : public MyApp::Scene
	{
	private:

		int                   _generateLightFrameCount; // ���𐶐�����܂ł̃t���[����
		std::list<TitleLight> _lightList;               // ���̃��X�g

		RectF            _cursor;                  // �w�肵���{�^���͈̔�

	public:

		TitleScene();

		void init() override;

		void update() override;

		void updateFadeOut(double) override;

		void draw()const override;

	};

}