#pragma once


#include<Siv3D.hpp>
#include<HamFramework.hpp>


struct ShareData
{
	/*
	�V�[���J�ڎ��̃f�[�^
	Event��Game�̃f�[�^�̃t�@�C����
	*/
	String sceneInfo;
};


using MyApp = SceneManager<String, ShareData>;