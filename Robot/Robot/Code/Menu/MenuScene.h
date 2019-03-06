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

		String _selectedWindowName; // �I������Ă���E�B���h�E�̖��O
		std::unordered_map<String, std::shared_ptr<MenuWindowBase>> _windowMap; // �E�B���h�E�̃}�b�v

	public:

		MenuScene();

	private:

		void update() override;

		void draw() const override;

	private:

		/// <summary>
		/// �E�B���h�E���J���܂��B
		/// </summary>
		/// <param name="windowName"> �J���E�B���h�E�̖��O </param>
		void openWindow(const String & windowName);

		/// <summary>
		/// �E�B���h�E����܂��B
		/// </summary>
		/// <param name="windowName"> �V�����I������E�B���h�E�̖��O </param>
		void closeWindow(const String & windowName);

	};
}