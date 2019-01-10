﻿
#include"Main.h"
#include"Input\InputManager.h"
#include"Title\TitleScene.h"
#include"SaveData\LoadSaveDataScene.h"
#include"Event\EventManager.h"
#include"Event\Factor\GenerateEvent.h"


void asseter(const String & dirname);


void Main()
{
	// 画像をアセット管理
	asseter(L"Asset/");

	// フォントのアセット管理
	FontAsset::Register(L"20", 20, L"メイリオ");

	// 各クラスの準備
	Robot::GenerateEvent::setObjectMap();
	Robot::EventManager::Instance().setAllEvent();

	// シーンの準備
	MyApp sceneManager;
	sceneManager.add<Robot::TitleScene>(L"TitleScene");
	sceneManager.add<Robot::LoadSaveDataScene>(L"LoadSaveDataScene");

	while (System::Update())
	{
		sceneManager.updateAndDraw();

		Robot::InputManager::Instance().changeState();
	}
}


void asseter(const String & direname)
{
	// 指定されたディレクトリのファイルパスを配列に
	Array<FilePath> contents = FileSystem::DirectoryContents(direname);

	for (const auto& content : contents)
	{

		String filename = FileSystem::FileName(content);


		// 指定されたパスがディレクトリであるとき
		if (FileSystem::IsDirectory(content))
		{
			asseter(direname + filename + L"/"); // 関数を再び呼ぶ
		}


		// 指定されたパスがファイルであるとき
		else if (FileSystem::IsFile(content))
		{

			// 拡張子がpngのとき
			if (FileSystem::Extension(content) == L"png")
			{
				TextureAsset::Register(FileSystem::BaseName(content), direname + filename);
			}

			// 拡張子がmp3のとき
			else if (FileSystem::Extension(content) == L"mp3")
			{
				SoundAsset::Register(FileSystem::BaseName(content), direname + filename);
			}

		}
	}
}