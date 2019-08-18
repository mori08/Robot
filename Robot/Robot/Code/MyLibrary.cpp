#include "MyLibrary.h"


#ifdef _DEBUG
void Robot::printError(const String & message)
{
	Println(message);
}
#else
void Robot::printError(const String &)
{
	
}
#endif // _DEBUG



void Robot::asseter(const String & dirname)
{
	// 指定されたディレクトリのファイルパスを配列に
	Array<FilePath> contents = FileSystem::DirectoryContents(dirname);

	for (const auto& content : contents)
	{

		String filename = FileSystem::FileName(content);


		// 指定されたパスがディレクトリであるとき
		if (FileSystem::IsDirectory(content))
		{
			asseter(dirname + filename + L"/"); // 関数を再び呼ぶ
		}


		// 指定されたパスがファイルであるとき
		else if (FileSystem::IsFile(content))
		{

			// 拡張子がpngのとき
			if (FileSystem::Extension(content) == L"png")
			{
				TextureAsset::Register(FileSystem::BaseName(content), dirname + filename);
			}

			// 拡張子がmp3のとき
			else if (FileSystem::Extension(content) == L"mp3")
			{
				SoundAsset::Register(FileSystem::BaseName(content), dirname + filename);
			}

		}
	}
}
