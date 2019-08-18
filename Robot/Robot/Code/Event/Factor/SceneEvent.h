#pragma once


#include "../EventManager.h"


namespace Robot
{
	/*
	SceneEventクラス
	シーン遷移を行います
	*/
	class SceneEvent : public EventBase
	{
	private:

		String _sceneName; // シーンの遷移先

		String _sceneInfo; // 遷移先のシーンで用いる補足情報

	private:

		bool load(const Info & info) override;

		void perform() const override;

		bool isCompleted() const override;

	};
}