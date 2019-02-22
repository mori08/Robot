#include "GameManager.h"
#include "Object\TestGameObject.h"
#include "Object\GamePlayer.h"
#include "Object\GameGoal.h"
#include "Object\HorizontalEnemy.h"
#include "Object\VerticalEnemy.h"
#include "Object\ChaseEnemy.h"
#include "Object\RunAwayGoal.h"
#include "Object\RandomEnemy.h"
#include "Object\AssassinEnemy.h"
#include "Object\GiantEnemy.h"
#include "Object\ChaseLightCentipede.h"
#include "State\PlayingState.h"
#include "State\GameClearState.h"
#include "State\GameOverState.h"


namespace
{
	const size_t POINT_COLUMNS   = 2; // 座標を示す行の列数
	const size_t POINT_X         = 0; // X座標のインデックス
	const size_t POINT_Y         = 1; // Y座標のインデックス
	const size_t OBJ_NUM_COLUMN  = 0; // オブジェクトの数が記載されている列番号
	const size_t OBJ_TYPE_COLUMN = 2; // オブジェクトの種類が記述されている列番号
}


Robot::GameManager::FuncMap Robot::GameManager::genarateEnemyMap;


void Robot::GameManager::setObjMap()
{
	makeGenerateFunc<GamePlayer>         (L"Player");
	makeGenerateFunc<GameGoal>           (L"Goal");
	makeGenerateFunc<RunAwayGoal>        (L"RunAwayGoal");
	makeGenerateFunc<HorizontalEnemy>    (L"Horizontal");
	makeGenerateFunc<VerticalEnemy>      (L"Vertical");
	makeGenerateFunc<ChaseEnemy>         (L"Chase");
	makeGenerateFunc<RandomEnemy>        (L"Random");
	makeGenerateFunc<AssassinEnemy>      (L"Assassin");
	makeGenerateFunc<GiantEnemy>         (L"Giant");
	makeGenerateFunc<ChaseLightCentipede>(L"ChaseLightCentipede");
}


Optional<Vec2> Robot::GameManager::getPointFromCSVReader(const CSVReader & csvReader, size_t readingRow)
{
	Optional<int> optX = FromStringOpt<int>(csvReader.get<String>(readingRow, POINT_X));
	Optional<int> optY = FromStringOpt<int>(csvReader.get<String>(readingRow, POINT_Y));
	if (!optX || !optY)
	{
		printError(L"Error > getPointFromCSVReaderで座標を変換できませんでした");
		printError(ToString(readingRow) + L"行目");
		printError(L"x : " + csvReader.get<String>(readingRow, POINT_X));
		printError(L"y : " + csvReader.get<String>(readingRow, POINT_Y));
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

	// オブジェクトの数の確認
	if (gameData.rows < readingRow)
	{
		printError(L"Error > GameDataの行数が足りません");
		return;
	}
	int objNum = gameData.get<int>(readingRow, OBJ_NUM_COLUMN); // 敵の数

	// オブジェクトの生成
	for (int i = 0; i < objNum; ++i)
	{
		if (gameData.rows < ++readingRow)
		{
			printError(L"Error > GameDataの行数が足りません");
			return;
		}

		Optional<Vec2> pos = getPointFromCSVReader(gameData, readingRow);
		if (!pos) 
		{
			return; 
		}
		String enemyType = gameData.get<String>(readingRow, OBJ_TYPE_COLUMN);
		if (genarateEnemyMap.find(enemyType) == genarateEnemyMap.end()) 
		{
			printError(L"Error > 存在しない敵の種類" + enemyType);
			return; 
		}
		_objList.emplace_back(genarateEnemyMap[enemyType](*pos));
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
	static bool debugMode = false;

	debugMode = debugMode^Input::Key0.clicked;

	if (debugMode)
	{
		// 光を薄く描画
		Window::ClientRect().draw(Color(Palette::MyWhite, 128));
		// マス目を描画
		for (int i = 0; i < StageData::N; ++i)
		{
			Rect(StageData::SIZE*StageData::intToPoint(i), StageData::SIZE).drawFrame(1, 1, Palette::MyBlack);
		}
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

