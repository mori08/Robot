#include "GameManager.h"


void Robot::GameManager::load(const String & gameDataFileName)
{
	_stageData.clear();

	CSVReader gameData(gameDataFileName);
	if (!gameData.isOpened())
	{
		printError(L"Error > GameDataを読み込めませんでした。 : " + gameDataFileName);
		return;
	}

	// ステージデータの設定
	if (gameData.rows < StageData::HEIGHT)
	{
		printError(L"Error > GameDataをステージデータの行数が足りません。");
		printError(L"rows : " + ToString(gameData.rows));
		return;
	}
	for (int y = 0; y < StageData::HEIGHT; ++y)
	{
		if (gameData.columns(y) < StageData::WIDTH)
		{
			printError(L"Error > GameDataをステージデータの列数が足りません。");
			printError(L"columns : " + ToString(gameData.columns(y)));
			return;
		}
		for (int x = 0; x < StageData::WIDTH; ++x)
		{
			_stageData.setWall(x, y);
		}
	}
}
