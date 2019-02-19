#pragma once


#include "../Main.h"
#include "Window\MenuWindowBase.h"


namespace Robot
{
	/*
	MenuScene�N���X
	ButtonList���Ǘ���
	Menu�𑀍삵�܂�
	*/
	class MenuScene : public MyApp::Scene
	{
	private:

		std::list<std::shared_ptr<MenuWindowBase>> _windowStack;

		std::unordered_map<String, std::shared_ptr<MenuWindowBase>> _windowList;

	public:

		MenuScene();

	private:

		void update() override;

		void draw() const override;

	};
}