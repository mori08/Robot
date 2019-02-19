#pragma once


#include<Siv3D.hpp>
#include"../../Input/Button.h"


namespace Robot
{
	/*
	MenuWindowBaseクラス
	MenuSceneに表示するWindowwoを表す
	*/
	class MenuWindowBase
	{
	private:

		using ProcessingPtr = std::unique_ptr<std::function<void()>>;

	protected:

		std::vector<std::shared_ptr<Button>>      _buttonPtrList; // ボタンのポインタのリスト
		
		std::unordered_map<String, Color>         _colorMap;      // 色のリスト ボタンのキーと結びつける

		std::unordered_map<String, ProcessingPtr> _processingMap; // ボタンを押したときの処理リスト

	public:

		/// <summary>
		/// 更新
		/// </summary>
		virtual void update() = 0;

		/// <summary>
		/// 描画
		/// </summary>
		virtual void draw() const = 0 ;

		/// <summary>
		/// InputManagerにボタンの情報を更新します。
		/// </summary>
		virtual void updateInputManager() const = 0;

		/// <summary>
		/// ボタンを押したときの処理を設定します。
		/// </summary>
		/// <param name="buttonKey"> ボタンのキー </param>
		/// <param name="processing"> ボタンを押したときの処理 </param>
		void setClickedProcessing(const String & buttonKey, ProcessingPtr processing);
		
	protected:

		/// <summary>
		/// 指定されたキーを持つボタンがあるか示します。
		/// </summary>
		/// <param name="buttonKey"> ボタンのキー </param>
		/// <returns> キーがあるとき true , そうでないとき false </returns>
		/// <remarks>
		/// O(ボタンの数)だけの時間がかかります
		/// </remarks>
		bool keyExistsAtButtonList(const String & buttonKey) const;

	};
}
