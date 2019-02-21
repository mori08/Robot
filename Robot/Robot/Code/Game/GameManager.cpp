#include "GameManager.h"
#include "Object\TestGameObject.h"
#include "Object\GamePlayer.h"
#include "Object\GameGoal.h"
#include "Object\HorizontalEnemy.h"
#include "Object\VerticalEnemy.h"
#include "State\PlayingState.h"
#include "State\GameClearState.h"
#include "State\GameOverState.h"


namespace
{
	const size_t POINT_COLUMNS     = 2; // 座標を示す行の列数
	const size_t POINT_X           = 0; // X座標のインデックス
	const size_t POINT_Y           = 1; // Y座標のインデックス
	const size_t ENEMY_NUM_COLUMN  = 0; // 敵の数が記載されている列番号
	const size_t ENEMY_TYPE_COLUMN = 2; // 敵の種類が記述されている列番号
}


Robot::GameManager::FuncMap Robot::GameManager::genarateEnemyMap;


void Robot::GameManager::setObjMap()
{
	makeGenerateFunc<HorizontalEnemy>(L"Horizontal");
	makeGenerateFunc<VerticalEnemy>(L"Vertical");
}


Optional<Vec2> Robot::GameManager::getPointFromCSVReader(const CSVReader & csvReader, size_t readingRow)
{
	Optional<int> optX = FromStringOpt<int>(csvReader.get<String>(readingRow, POINT_X));
	Optional<int> optY = FromStringOpt<int>(csvReader.get<String>(readingRow, POINT_Y));
	if (!optX || !optY)
	{
		printError(L"Error > getPointFromCSVReaderで座標を変換できませんでした");
		return none;
	}

	return Optional<Vec2>(_stageData.SIZE*Point(*optX, *optY) + _stageData.SIZE*0.5*Vec2::One);
}


void Robot::GameManager::init()
{
	_gameState = std::make_unique<PlayingState>();
	_objList.clear();
	_stageData.clear();
	_isChangeAbleScene = false;
	_sceneName = L"";
	_sceneInfo = L"";
}


void Robot::GameManager::load(const String & gameDataFileName)
{
	init();

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
	Optional<Vec2> playerPos = getPointFromCSVReader(gameData, readingRow);
	if (!playerPos) { return; }
	_objList.emplace_back(std::make_unique<GamePlayer>(*playerPos));

	// ゴールの生成
	if (gameData.rows < ++readingRow)
	{
		printError(L"Error > GameDataの行数が足りません");
		return;
	}
	Optional<Vec2> goalPos = getPointFromCSVReader(gameData, readingRow);
	if (!goalPos) { return; }
	_objList.emplace_back(std::make_unique<GameGoal>(*goalPos));

	// 敵の数の確認
	if (gameData.rows < ++readingRow)
	{
		printError(L"Error > GameDataの行数が足りません");
		return;
	}
	int enemyNum = gameData.get<int>(readingRow, ENEMY_NUM_COLUMN); // 敵の数

	// 敵の生成
	for (int i = 0; i < enemyNum; ++i)
	{
		if (gameData.rows < ++readingRow)
		{
			printError(L"Error > GameDataの行数が足りません");
			return;
		}

		Optional<Vec2> enemyPos = getPointFromCSVReader(gameData, readingRow);
		if (!enemyPos) 
		{
			printError(L"Error > 座標に変換できません");
			return; 
		}
		String enemyType = gameData.get<String>(readingRow, ENEMY_TYPE_COLUMN);
		if (genarateEnemyMap.find(enemyType) == genarateEnemyMap.end()) 
		{
			printError(L"Error > 存在しない敵の種類" + enemyType);
			return; 
		}
		_objList.emplace_back(genarateEnemyMap[enemyType](*enemyPos));
	}


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


void Robot::GameManager::gameClear()
{
	_gameState = std::make_unique<GameClearState>();
}


void Robot::GameManager::gameOver()
{
	_gameState = std::make_unique<GameOverState>();
}

