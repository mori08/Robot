
#include"Main.h"
#include"Input\InputManager.h"
#include"Title\TitleScene.h"


void asseter(const String & dirname);


void Main()
{
	asseter(L"Asset/");

	MyApp sceneManager;

	sceneManager.add<Robot::TitleScene>(L"TitleScene");

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