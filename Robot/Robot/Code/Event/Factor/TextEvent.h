#pragma once


#include "../EventManager.h"


namespace Robot
{
	/*
	TextEventクラス
	TextBoxの関数を使用し、
	テキストの表示を行う。
	*/
	class TextEvent : public EventBase
	{
	private:

		String _speakerName; // 話し手の名前

		String _iconName;    // アイコンの画像の名前

		int    _textSpeed;   // テキストを表示する速さ

		String _text;        // 表示するテキスト

	private:

		bool load(const Info & info) override;

		void perform() const override;

		bool isCompleted() const override;

	};
}