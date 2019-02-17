#include "GameManager.h"
#include "Object\TestGameObject.h"
#include "Object\GamePlayer.h"
#include "Object\GameGoal.h"
#include "State\PlayingState.h"


namespace
{
	const size_t POINT_COLUMNS = 2; // 座標を示す行の列数
	const size_t POINT_X = 0;       // X座標のインデックス
	const size_t POINT_Y = 1;       // Y座標のインデックス
}


Optional<Point> Robot::GameManager::getPointFromCSVReader(const CSVReader & csvReader, size_t readingRow)
{
	Optional<int> optX = FromStringOpt<int>(csvReader.get<String>(readingRow, POINT_X));
	Optional<int> optY = FromStringOpt<int>(csvReader.get<String>(readingRow, POINT_Y));
	if (!optX || !optY)
	{
		printError(L"Error > getPointFromCSVReaderで座標を変換できませんでした");
		return none;
	}

	return Optional<Point>(Point(*optX, *optY));
}


void Robot::GameManager::load(const String & gameDataFileName)
{
	_state = State::PLAYING;
	_objList.clear();
	_stageData.clear();
	_gameState = std::make_unique<PlayingState>();

	int readingRow = 0;

	CSVReader gameData(gameDataFileName);
	if (!gameData.isOpened())
	{
		printError(L"Error > GameDataを読み込めませんでした。 : " + gameDataFileName);
		return;
	}

	// ステージデータの設定
	if (gameData.rows < StageData::HEIGHT)
	{
		printError(L"Error > GameDataの行数が足りません");
		return;
	}
	for (readingRow = 0; readingRow < StageData::HEIGHT; ++readingRow)
	{
		if (gameData.columns(readingRow) < StageData::WIDTH)
		{
			printError(L"Error > GameDataのステージデータの列数が足りません。");
			printError(L"columns : " + ToString(gameData.columns(readingRow)));
			return;
		}
		for (int x = 0; x < StageData::WIDTH; ++x)
		{
			if (gameData.get<int>(readingRow, x) == 1)
			{
				_stageData.setWall(x, readingRow);
			}
		}
	}

	// 経路探索
	_stageData.searchPath();

	// プレイヤーの生成
	if (gameData.rows < readingRow)
	{
		printError(L"Error > GameDataの行数が足りません");
		return;
	}
	Optional<Point> playerPos = getPointFromCSVReader(gameData, readingRow);
	if (!playerPos) { return; }
	_objList.emplace_back(std::make_unique<GamePlayer>(_stageData.SIZE*(*playerPos)));

	// ゴールの生成
	if (gameData.rows < ++readingRow)
	{
		printError(L"Error > GameDataの行数が足りません");
		return;
	}
	Optional<Point> goalPos = getPointFromCSVReader(gameData, readingRow);
	if (!goalPos) { return; }
	_objList.emplace_back(std::make_unique<GameGoal>(_stageData.SIZE*(*goalPos)));

	// 光の初期位置の設定
	_light.setPos(Window::Center());
}


void Robot::GameManager::update()
{
	_gameState->update(*this);
}


void Robot::GameManager::draw() const
{
	_gameState->draw(*this);
}


bool Robot::GameManager::isChangeAbleScene(String & sceneName, String & sceneInfo) const
{
	if (_isChangeAbleScene)
	{
		sceneName = _sceneName;
		sceneInfo = _sceneInfo;
	}

	return _isChangeAbleScene;
}


void Robot::GameManager::updateObjectAndLight()
{
	_light.update();

	for (auto && obj : _objList)
	{
		obj->update(*this);
	}
}


void Robot::GameManager::drawObjectAndLight() const
{
#ifdef _DEBUG
	if (Input::Key0.pressed)
	{
		// 光を薄く描画
		Window::ClientRect().draw(Color(Palette::MyWhite, 128));
	}
#endif // _DEBUG

	_light.draw();

	for (const auto & obj : _objList)
	{
		obj->draw();
	}

	_stageData.draw();
}


void Robot::GameManager::setSceneName(const String & sceneName, const String & sceneInfo)
{
	_isChangeAbleScene = true;
	_sceneName = sceneName;
	_sceneInfo = sceneInfo;
}
