#pragma once


#include"../EventManager.h"


namespace Robot
{
	/*
	InitEventクラス
	オブジェクトの初期化を行います。
	Run命令より前に使用する
	*/
	class InitEvent : public EventBase
	{
	private:

		String _objectName; // オブジェクトの名前

		String _initName;   // 初期化関数の名前

	private:

		bool load(const Info & info) override;

		void perform() const override;

		bool isCompleted() const override;

	};
}