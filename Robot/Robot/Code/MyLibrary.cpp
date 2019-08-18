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
	// �w�肳�ꂽ�f�B���N�g���̃t�@�C���p�X��z���
	Array<FilePath> contents = FileSystem::DirectoryContents(dirname);

	for (const auto& content : contents)
	{

		String filename = FileSystem::FileName(content);


		// �w�肳�ꂽ�p�X���f�B���N�g���ł���Ƃ�
		if (FileSystem::IsDirectory(content))
		{
			asseter(dirname + filename + L"/"); // �֐����ĂьĂ�
		}


		// �w�肳�ꂽ�p�X���t�@�C���ł���Ƃ�
		else if (FileSystem::IsFile(content))
		{

			// �g���q��png�̂Ƃ�
			if (FileSystem::Extension(content) == L"png")
			{
				TextureAsset::Register(FileSystem::BaseName(content), dirname + filename);
			}

			// �g���q��mp3�̂Ƃ�
			else if (FileSystem::Extension(content) == L"mp3")
			{
				SoundAsset::Register(FileSystem::BaseName(content), dirname + filename);
			}

		}
	}
}
