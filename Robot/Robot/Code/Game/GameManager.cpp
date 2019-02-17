#include "GameManager.h"
#include "Object\TestGameObject.h"
#include "Object\GamePlayer.h"
#include "Object\GameGoal.h"
#include "State\PlayingState.h"
#include "State\GameClearState.h"
#include "State\GameOverState.h"


namespace
{
	const size_t POINT_COLUMNS = 2; // ���W�������s�̗�
	const size_t POINT_X = 0;       // X���W�̃C���f�b�N�X
	const size_t POINT_Y = 1;       // Y���W�̃C���f�b�N�X
}


Optional<Point> Robot::GameManager::getPointFromCSVReader(const CSVReader & csvReader, size_t readingRow)
{
	Optional<int> optX = FromStringOpt<int>(csvReader.get<String>(readingRow, POINT_X));
	Optional<int> optY = FromStringOpt<int>(csvReader.get<String>(readingRow, POINT_Y));
	if (!optX || !optY)
	{
		printError(L"Error > getPointFromCSVReader�ō��W��ϊ��ł��܂���ł���");
		return none;
	}

	return Optional<Point>(Point(*optX, *optY));
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
		printError(L"Error > GameData��ǂݍ��߂܂���ł����B : " + gameDataFileName);
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

	// �v���C���[�̐���
	if (gameData.rows < readingRow)
	{
		printError(L"Error > GameData�̍s��������܂���");
		return;
	}
	Optional<Point> playerPos = getPointFromCSVReader(gameData, readingRow);
	if (!playerPos) { return; }
	_objList.emplace_back(std::make_unique<GamePlayer>(_stageData.SIZE*(*playerPos)));

	// �S�[���̐���
	if (gameData.rows < ++readingRow)
	{
		printError(L"Error > GameData�̍s��������܂���");
		return;
	}
	Optional<Point> goalPos = getPointFromCSVReader(gameData, readingRow);
	if (!goalPos) { return; }
	_objList.emplace_back(std::make_unique<GameGoal>(_stageData.SIZE*(*goalPos)));

	// ���̏����ʒu�̐ݒ�
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
		// ���𔖂��`��
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

