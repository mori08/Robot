#include "GameManager.h"


void Robot::GameManager::load(const String & gameDataFileName)
{
	_stageData.clear();

	CSVReader gameData(gameDataFileName);
	if (!gameData.isOpened())
	{
		printError(L"Error > GameData��ǂݍ��߂܂���ł����B : " + gameDataFileName);
		return;
	}

	// �X�e�[�W�f�[�^�̐ݒ�
	if (gameData.rows < StageData::HEIGHT)
	{
		printError(L"Error > GameData���X�e�[�W�f�[�^�̍s��������܂���B");
		printError(L"rows : " + ToString(gameData.rows));
		return;
	}
	for (int y = 0; y < StageData::HEIGHT; ++y)
	{
		if (gameData.columns(y) < StageData::WIDTH)
		{
			printError(L"Error > GameData���X�e�[�W�f�[�^�̗񐔂�����܂���B");
			printError(L"columns : " + ToString(gameData.columns(y)));
			return;
		}
		for (int x = 0; x < StageData::WIDTH; ++x)
		{
			_stageData.setWall(x, y);
		}
	}
}
