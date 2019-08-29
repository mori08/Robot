#pragma once


#include "Window\MenuWindowBase.h"


namespace Robot
{
	/*
	MenuManager�N���X
	�E�B���h�E���Ǘ������܂��B
	*/
	class MenuManager
	{
	private:

		using WindowPtr = std::unique_ptr<MenuWindowBase>;
		using WindowMap = std::unordered_map<String, WindowPtr>;

		using SceneName = std::pair<String, String>;

	private:

		String    _selectedWindowName; // �I������Ă���E�B���h�E�̖��O

		WindowMap _windowMap;          // �E�B���h�E�̃}�b�v
		
		bool      _isChangeAbleScene;  // �V�[���J�ڂ��\�Ȃ� true

		SceneName _sceneName;          // { �V�[����, �J�ڐ�̕⑫ }

	private:

		MenuManager();

		MenuManager(const MenuManager &)             = default; 
		MenuManager & operator=(const MenuManager &) = default;
		MenuManager(MenuManager &&)                  = default;
		MenuManager & operator=(MenuManager &&)      = default;

	public: // �V�[���Ŏg�p����֐�

		/// <summary>
		/// �V���O���g���Ƃ��ĊǗ����Ă���MenuManager�̃C���X�^���X���擾���܂��B
		/// </summary>
		/// <returns> �C���X�^���X </returns>
		static MenuManager & Instance()
		{
			static MenuManager instance;
			return instance;
		}

		/// <summary>
		/// �X�V
		/// </summary>
		void update();

		/// <summary>
		/// �`��
		/// </summary>
		void draw() const;

		/// <summary>
		/// ���j���[���Z�[�u�f�[�^���Q�Ƃ��č�蒼���܂��B
		/// </summary>
		void load();

		/// <summary>
		/// �V�[����ύX����
		/// </summary>
		/// <param name="sceneName"> �V�[���̖��O </param>
		/// <param name="sceneInfo"> �V�[���J�ڌ�Ɉ��������� </param>
		/// <returns> �V�[���J�ډ\�ȂƂ� true , �����łȂ��Ƃ� false </returns>
		bool isChangeAbleScene(String & sceneName, String & sceneInfo) const;

	public: // WindowBase�̔h���N���X�Ŏg�p����֐�

		/// <summary>
		/// �E�B���h�E���J���܂��B
		/// </summary>
		/// <param name="windowName"> �J���E�B���h�E�̖��O </param>
		void openWindow(const String & windowName);

		/// <summary>
		/// �E�B���h�E����܂��B
		/// </summary>
		void closeWindow(const String & windowName);

		/// <summary>
		/// �V�[���̑J�ڐ��ݒ肵�܂��B
		/// </summary>
		void setSceneName(const String & sceneName, const String & sceneInfo);

	};
}