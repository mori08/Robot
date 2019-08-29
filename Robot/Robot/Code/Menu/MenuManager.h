#pragma once


#include "Window\MenuWindowBase.h"


namespace Robot
{
	/*
	MenuManagerクラス
	ウィンドウを管理をします。
	*/
	class MenuManager
	{
	private:

		using WindowPtr = std::unique_ptr<MenuWindowBase>;
		using WindowMap = std::unordered_map<String, WindowPtr>;

		using SceneName = std::pair<String, String>;

	private:

		String    _selectedWindowName; // 選択されているウィンドウの名前

		WindowMap _windowMap;          // ウィンドウのマップ
		
		bool      _isChangeAbleScene;  // シーン遷移が可能なら true

		SceneName _sceneName;          // { シーン名, 遷移先の補足 }

	private:

		MenuManager();

		MenuManager(const MenuManager &)             = default; 
		MenuManager & operator=(const MenuManager &) = default;
		MenuManager(MenuManager &&)                  = default;
		MenuManager & operator=(MenuManager &&)      = default;

	public: // シーンで使用する関数

		/// <summary>
		/// シングルトンとして管理しているMenuManagerのインスタンスを取得します。
		/// </summary>
		/// <returns> インスタンス </returns>
		static MenuManager & Instance()
		{
			static MenuManager instance;
			return instance;
		}

		/// <summary>
		/// 更新
		/// </summary>
		void update();

		/// <summary>
		/// 描画
		/// </summary>
		void draw() const;

		/// <summary>
		/// メニューをセーブデータを参照して作り直します。
		/// </summary>
		void load();

		/// <summary>
		/// シーンを変更する
		/// </summary>
		/// <param name="sceneName"> シーンの名前 </param>
		/// <param name="sceneInfo"> シーン遷移後に扱う文字列 </param>
		/// <returns> シーン遷移可能なとき true , そうでないとき false </returns>
		bool isChangeAbleScene(String & sceneName, String & sceneInfo) const;

	public: // WindowBaseの派生クラスで使用する関数

		/// <summary>
		/// ウィンドウを開きます。
		/// </summary>
		/// <param name="windowName"> 開くウィンドウの名前 </param>
		void openWindow(const String & windowName);

		/// <summary>
		/// ウィンドウを閉じます。
		/// </summary>
		void closeWindow(const String & windowName);

		/// <summary>
		/// シーンの遷移先を設定します。
		/// </summary>
		void setSceneName(const String & sceneName, const String & sceneInfo);

	};
}