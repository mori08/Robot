#pragma once


#include<Siv3D.hpp>
#include<HamFramework.hpp>


struct ShareData
{
	/*
	シーン遷移時のデータ
	EventやGameのデータのファイル名
	*/
	String sceneInfo;
};

using MyApp = SceneManager<String, ShareData>;


namespace Robot
{
	/// <summary>
	/// デバッグ用の文字列を出力します。
	/// </summary>
	/// <param name="message"> 出力する文字列 </param>
	void printError(const String & message);

	/// <summary>
	/// アセット管理
	/// </summary>
	/// <param name="dirname"> ディレクトリの名前 </param>
	void asseter(const String & dirname);

}