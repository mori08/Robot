#pragma once


#include "../Main.h"
#include "Window\MenuWindowBase.h"


namespace Robot
{
	/*
	MenuSceneクラス
	ButtonListを管理し
	Menuを操作します
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

	private:

		/// <summary>
		/// ウィンドウを開きます。
		/// </summary>
		/// <param name="windowName"> 開くウィンドウの名前 </param>
		void openWindow(const String & windowName);

	};
}