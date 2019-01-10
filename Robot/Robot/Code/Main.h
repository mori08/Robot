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