#pragma once


#include "../Main.h"
#include "Window\MenuWindowBase.h"


namespace Robot
{
	/*
	MenuSceneƒNƒ‰ƒX
	ButtonList‚ğŠÇ—‚µ
	Menu‚ğ‘€ì‚µ‚Ü‚·
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