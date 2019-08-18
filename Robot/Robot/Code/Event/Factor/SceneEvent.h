#pragma once


#include "../EventManager.h"


namespace Robot
{
	/*
	SceneEvent�N���X
	�V�[���J�ڂ��s���܂�
	*/
	class SceneEvent : public EventBase
	{
	private:

		String _sceneName; // �V�[���̑J�ڐ�

		String _sceneInfo; // �J�ڐ�̃V�[���ŗp����⑫���

	private:

		bool load(const Info & info) override;

		void perform() const override;

		bool isCompleted() const override;

	};
}