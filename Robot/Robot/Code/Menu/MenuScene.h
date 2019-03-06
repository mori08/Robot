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

		String _selectedWindowName; // 選択されているウィンドウの名前
		std::unordered_map<String, std::shared_ptr<MenuWindowBase>> _windowMap; // ウィンドウのマップ

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

		/// <summary>
		/// ウィンドウを閉じます。
		/// </summary>
		/// <param name="windowName"> 新しく選択するウィンドウの名前 </param>
		void closeWindow(const String & windowName);

	};
}