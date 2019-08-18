#include "../MyLibrary.h"
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
#include "Object\RandomCentipede.h"
#include "Object\ChasePlayerCentipede.h"
#include "Object\GoalTailCentipede.h"
#include "Object\HorizontalBlockEnemy.h"
#include "Object\VerticalBlockEnemy.h"
#include "Object\LastGoal.h"
#include "Object\DefenceEnemy.h"
#include "Object\FlashEnemy.h"
#include "Object\DoctorEnemy.h"
#include "Object\LockGoal.h"
#include "Object\PatrolTeamEnemy.h"
#include "Object\FriendEnemy.h"
#include "State\PlayingState.h"
#include "State\GameClearState.h"
#include "State\GameOverState.h"
#include "State\TutorialOfPlayerMove.h"
#include "State\LoseState.h"
#include "State\AccessState.h"


namespace
{
	const size_t POINT_COLUMNS   = 2; // ���W�������s�̗�
	const size_t POINT_X         = 0; // X���W�̃C���f�b�N�X
	const size_t POINT_Y         = 1; // Y���W�̃C���f�b�N�X
	const size_t OBJ_NUM_COLUMN  = 0; // �I�u�W�F�N�g�̐����L�ڂ���Ă����ԍ�
	const size_t OBJ_TYPE_COLUMN = 2; // �I�u�W�F�N�g�̎�ނ��L�q����Ă����ԍ�

	const String LIGHT_OFF_TEXT = L"LightOFF"; // ���������e�L�X�g
}


Robot::GameManager::FuncMap Robot::GameManager::genarateEnemyMap;


void Robot::GameManager::setObjMap()
{
	makeGenerateFunc<GamePlayer>          (L"Player");
	makeGenerateFunc<GameGoal>            (L"Goal");
	makeGenerateFunc<RunAwayGoal>         (L"RunAwayGoal");
	makeGenerateFunc<LastGoal>            (L"LastGoal");
	makeGenerateFunc<HorizontalEnemy>     (L"Horizontal");
	makeGenerateFunc<VerticalEnemy>       (L"Vertical");
	makeGenerateFunc<ChaseEnemy>          (L"Chase");
	makeGenerateFunc<RandomEnemy>         (L"Random");
	makeGenerateFunc<AssassinEnemy>       (L"Assassin");
	makeGenerateFunc<GiantEnemy>          (L"Giant");
	makeGenerateFunc<RandomCentipede>     (L"RandomCentipede");
	makeGenerateFunc<ChasePlayerCentipede>(L"ChasePlayerCentipede");
	makeGenerateFunc<GoalTailCentipede>   (L"GoalTailCentipede");
	makeGenerateFunc<HorizontalBlockEnemy>(L"HorizontalBlock");
	makeGenerateFunc<VerticalBlockEnemy>  (L"VerticalBlock");
	makeGenerateFunc<DefenceEnemy>        (L"Defence");
	makeGenerateFunc<FlashEnemy>          (L"Flash");
	makeGenerateFunc<DoctorEnemy>         (L"Doctor");
	makeGenerateFunc<LockGoal>            (L"LockGoal");
	makeGenerateFunc<PatrolTeamEnemy>     (L"Patrol");
	makeGenerateFunc<FriendEnemy>         (L"Friend");
}


Optional<Vec2> Robot::GameManager::getPointFromCSVReader(const CSVReader & csvReader, size_t readingRow)
{
	Optional<int> optX = FromStringOpt<int>(csvReader.get<String>(readingRow, POINT_X));
	Optional<int> optY = FromStringOpt<int>(csvReader.get<String>(readingRow, POINT_Y));
	if (!optX || !optY)
	{
		printError(L"Error > getPointFromCSVReader�ō��W��ϊ��ł��܂���ł���");
		printError(ToString(readingRow) + L"�s��");
		printError(L"x : " + csvReader.get<String>(readingRow, POINT_X));
		printError(L"y : " + csvReader.get<String>(readingRow, POINT_Y));
		return none;
	}

	return Optional<Vec2>(_stageData.SIZE*Point(*optX, *optY) + _stageData.SIZE*0.5*Vec2::One);
}


void Robot::GameManager::init()
{
	_gameState = std::make_unique<AccessState>(false);
	_objList.clear();
	_stageData.clear();
	_isChangeAbleScene = false;
	_sceneName = L"";
	_sceneInfo = L"";

	// ���̏����ʒu�̐ݒ�
	_light.On();
	_light.setPos(Window::Center());
}


void Robot::GameManager::load(const String & gameDataFileName)
{
	init();

	int readingRow = 0;

	CSVReader gameData(gameDataFileName);
	if (!gameData.isOpened())
	{
		printError(L"Error > GameData��ǂݍ��߂܂���ł����B : " + gameDataFileName);
		return;
	}

	if (gameData.get<String>(0, 0) == L"Tutorial")
	{
		_gameState = std::make_unique<AccessState>(true);
		_objList.emplace_back(std::make_unique<GamePlayer>(Window::Center()));
		_light.setPos(Window::Center());
		return;
	}

	// �X�e�[�W�f�[�^�̐ݒ�
	if (gameData.rows < StageData::HEIGHT)
	{
		printError(L"Error > GameData�̍s��������܂���");
		return;
	}
	for (readingRow = 0; readingRow < StageData::HEIGHT; ++readingRow)
	{
		if (gameData.columns(readingRow) < StageData::WIDTH)
		{
			printError(L"Error > GameData�̃X�e�[�W�f�[�^�̗񐔂�����܂���B");
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

	// �o�H�T��
	_stageData.searchPath();

	// �I�u�W�F�N�g�̐��̊m�F
	if (gameData.rows < readingRow)
	{
		printError(L"Error > GameData�̍s��������܂���");
		return;
	}
	int objNum = gameData.get<int>(readingRow, OBJ_NUM_COLUMN); // �G�̐�

	// �I�u�W�F�N�g�̐���
	for (int i = 0; i < objNum; ++i)
	{
		if (gameData.rows < ++readingRow)
		{
			printError(L"Error > GameData�̍s��������܂���");
			return;
		}

		if (gameData.get<String>(readingRow, 0) == LIGHT_OFF_TEXT)
		{
			_light.Off();
			continue;
		}

		Optional<Vec2> pos = getPointFromCSVReader(gameData, readingRow);
		if (!pos) 
		{
			return; 
		}
		String enemyType = gameData.get<String>(readingRow, OBJ_TYPE_COLUMN);
		if (genarateEnemyMap.find(enemyType) == genarateEnemyMap.end()) 
		{
			printError(L"Error > ���݂��Ȃ��G�̎��" + enemyType);
			return; 
		}
		_objList.emplace_back(genarateEnemyMap[enemyType](*pos));
	}
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

#ifdef _DEBUG
	if (Input::KeyG.clicked)
	{
		gameClear();
	}
#endif // _DEBUG

}


void Robot::GameManager::drawObjectAndLight() const
{
#ifdef _DEBUG
	static bool debugMode = false;

	debugMode = debugMode^Input::Key0.clicked;

	if (debugMode)
	{
		// ���𔖂��`��
		Window::ClientRect().draw(Color(Palette::MyWhite, 128));
		// �}�X�ڂ�`��
		for (int i = 0; i < StageData::N; ++i)
		{
			Rect(StageData::SIZE*StageData::intToPoint(i), StageData::SIZE).drawFrame(1, 1, Palette::MyBlack);
		}
	}
#endif // _DEBUG

	_light.draw();

	for (const auto & obj : _objList)
	{
		obj->drawLight();
	}

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


void Robot::GameManager::makeTutorialGoal()
{
	static const std::vector<Vec2> GOAL_POS_LIST // �S�[���̌��n���X�g
	{
		Vec2(20 ,20),
		Vec2(620,20),
		Vec2(20 ,460),
		Vec2(620,460)
	};

	Vec2 goalPos;
	double max_dist = 0;

	for (const auto & pos : GOAL_POS_LIST)
	{
		double dist = (pos - getPlayerPos()).length();
		if (dist > max_dist)
		{
			max_dist = dist;
			goalPos = pos;
		}
	}

	_objList.emplace_back(std::make_unique<GameGoal>(goalPos));
}


void Robot::GameManager::gameClear()
{
	_gameState = std::make_unique<GameClearState>();
}


void Robot::GameManager::gameOver()
{
	_gameState = std::make_unique<GameOverState>();
}


void Robot::GameManager::lose()
{
	_gameState = std::make_unique<LoseState>();
}

