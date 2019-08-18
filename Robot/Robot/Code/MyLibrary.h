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


namespace Robot
{
	/// <summary>
	/// �f�o�b�O�p�̕�������o�͂��܂��B
	/// </summary>
	/// <param name="message"> �o�͂��镶���� </param>
	void printError(const String & message);

	/// <summary>
	/// �A�Z�b�g�Ǘ�
	/// </summary>
	/// <param name="dirname"> �f�B���N�g���̖��O </param>
	void asseter(const String & dirname);

}